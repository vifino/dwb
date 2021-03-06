/*
 * Copyright (c) 2010-2014 Stefan Bolte <portix@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <JavaScriptCore/JavaScript.h>
#include <string.h>
#include <math.h>
#include "dwb.h"
#include "util.h"
#include "js.h"
void
js_make_exception(JSContextRef ctx, JSValueRef *exception, const gchar *format, ...) 
{
    va_list arg_list; 

    va_start(arg_list, format);
    gchar message[STRING_LENGTH];
    vsnprintf(message, sizeof(message), format, arg_list);
    va_end(arg_list);
    *exception = js_char_to_value(ctx, message);
}

void 
js_set_property(JSContextRef ctx, JSObjectRef arg, const char *name, JSValueRef prop, JSClassAttributes attributes, JSValueRef *exc) 
{
    JSStringRef js_key = JSStringCreateWithUTF8CString(name);
    JSObjectSetProperty(ctx, arg, js_key, prop, attributes, exc);
    JSStringRelease(js_key);
}
gboolean 
js_string_equals(JSContextRef ctx, JSValueRef val, const char *cmp)
{
    gboolean result = false;
    if (JSValueIsString(ctx, val))
    {
        JSStringRef js_string = JSValueToStringCopy(ctx, val, NULL);
        if (js_string != NULL)
        {
            result = JSStringIsEqualToUTF8CString(js_string, cmp);
            JSStringRelease(js_string);
        }
    }
    return result;
}
void 
js_set_object_property(JSContextRef ctx, JSObjectRef arg, const char *name, const char *value, JSValueRef *exc) 
{
    g_return_if_fail(name != NULL);

    JSStringRef js_key = JSStringCreateWithUTF8CString(name);
    JSValueRef js_value;
    if (value != NULL)
        js_value = js_char_to_value(ctx, value);
    else 
        js_value = JSValueMakeNull(ctx);
        
    JSObjectSetProperty(ctx, arg, js_key, js_value, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly, exc);
    JSStringRelease(js_key);
}
gboolean 
js_object_has_property(JSContextRef ctx, JSObjectRef arg, const char *name)
{
    JSStringRef js_key = JSStringCreateWithUTF8CString(name);
    gboolean result = JSObjectHasProperty(ctx, arg, js_key);
    JSStringRelease(js_key);
    return result;
}
void 
js_set_object_number_property(JSContextRef ctx, JSObjectRef arg, const char *name, gdouble value, JSValueRef *exc) 
{
    JSStringRef js_key = JSStringCreateWithUTF8CString(name);
    JSValueRef js_value = JSValueMakeNumber(ctx, value);
    JSObjectSetProperty(ctx, arg, js_key, js_value, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly, exc);
    JSStringRelease(js_key);
}
/* js_get_object_property {{{*/
JSObjectRef 
js_get_object_property(JSContextRef ctx, JSObjectRef arg, const char *name) 
{
    JSValueRef exc = NULL;
    JSObjectRef ret;
    JSStringRef buffer = JSStringCreateWithUTF8CString(name);
    JSValueRef val = JSObjectGetProperty(ctx, arg, buffer, &exc);
    JSStringRelease(buffer);
    if (exc != NULL || !JSValueIsObject(ctx, val)) 
        return NULL;

    ret = JSValueToObject(ctx, val, &exc);
    if (exc != NULL)
        return NULL;
    return ret;
}/*}}}*/

JSValueRef 
js_char_to_value(JSContextRef ctx, const char *text) 
{
    JSStringRef string = JSStringCreateWithUTF8CString(text);
    JSValueRef ret = JSValueMakeString(ctx, string);
    JSStringRelease(string);
    return ret;
}
/* js_get_string_property {{{*/
char * 
js_get_string_property(JSContextRef ctx, JSObjectRef arg, const char *name) 
{
    JSValueRef exc = NULL;
    JSStringRef buffer = JSStringCreateWithUTF8CString(name);
    JSValueRef val = JSObjectGetProperty(ctx, arg, buffer, &exc);
    JSStringRelease(buffer);
    if (exc != NULL || !JSValueIsString(ctx, val) )
        return NULL;
    return js_value_to_char(ctx, val, JS_STRING_MAX, NULL);
}/*}}}*/

/* js_get_double_property {{{*/
double  
js_get_double_property(JSContextRef ctx, JSObjectRef arg, const char *name) 
{
    double ret;
    JSValueRef exc = NULL;
    JSStringRef buffer = JSStringCreateWithUTF8CString(name);
    JSValueRef val = JSObjectGetProperty(ctx, arg, buffer, &exc);
    JSStringRelease(buffer);
    if (exc != NULL || !JSValueIsNumber(ctx, val) )
        return NAN;
    ret = JSValueToNumber(ctx, val, &exc);
    if (exc != NULL)
        return NAN;
    return ret;
}/*}}}*/
double 
js_val_get_double_property(JSContextRef ctx, JSValueRef val, const char *name, JSValueRef *exc)
{
    JSObjectRef o = JSValueToObject(ctx, val, exc);
    if (o != NULL)
    {
        return js_get_double_property(ctx, o, name);
    }
    return NAN;

}

/* js_string_to_char 
 * Converts a JSStringRef, return a newly allocated char.
 * {{{*/
char *
js_string_to_char(JSContextRef ctx, JSStringRef jsstring, size_t size) 
{
    size_t length;
    if (size > 0) 
        length = MIN(JSStringGetMaximumUTF8CStringSize(jsstring), size);
    else 
        length = JSStringGetMaximumUTF8CStringSize(jsstring);

    char *ret = g_malloc(sizeof(gchar) * length);
    JSStringGetUTF8CString(jsstring, ret, length);
    return ret;
}/*}}}*/

JSValueRef 
js_context_change(JSContextRef source_ctx, JSContextRef dest_ctx, JSValueRef val, JSValueRef *exc) 
{
    char *c_val = js_value_to_json(source_ctx, val, -1, 0, exc);
    if (c_val == NULL)
        return JSValueMakeNull(dest_ctx);

    JSStringRef json = JSStringCreateWithUTF8CString(c_val);
    JSValueRef ret = JSValueMakeFromJSONString(dest_ctx, json);

    g_free(c_val);
    JSStringRelease(json);

    if (ret == NULL)
        return JSValueMakeNull(dest_ctx);
    return ret;
}

/* js_create_object(WebKitWebFrame *frame, const char *) 
 *
 * Executes a script in a function scope, should return an object with
 * function-properties
 * {{{*/
JSObjectRef 
js_create_object(WebKitWebFrame *frame, const char *script) 
{
    if (script == NULL)
        return NULL;

    JSStringRef js_script;
    JSValueRef ret, exc = NULL;
    JSObjectRef return_object;

    JSContextRef ctx = webkit_web_frame_get_global_context(frame);
    js_script = JSStringCreateWithUTF8CString(script);
    ret = JSEvaluateScript(ctx, js_script, NULL, NULL, 0, &exc);
    JSStringRelease(js_script);
    if (exc != NULL)
        return NULL;

    return_object = JSValueToObject(ctx, ret, &exc);
    if (exc != NULL)
        return NULL;
    JSValueProtect(ctx, ret);
    return return_object;
}/*}}}*/

/* js_call_as_function(WebKitWebFrame, JSObjectRef, char *string, char *json, * char **ret) {{{*/
char *  
js_call_as_function(WebKitWebFrame *frame, JSObjectRef obj, const char *string, const char *json, JSType arg_type, char **char_ret) 
{
    char *ret = NULL;
    JSValueRef js_ret, function, v = NULL;
    JSObjectRef function_object;
    JSStringRef js_json, js_name = NULL;
    JSContextRef ctx;

    if (obj == NULL)  
        goto error_out;

    ctx = webkit_web_frame_get_global_context(frame);
    js_name = JSStringCreateWithUTF8CString(string);

    if (!JSObjectHasProperty(ctx, obj, js_name)) 
        goto error_out;

    function = JSObjectGetProperty(ctx, obj, js_name, NULL);
    function_object = JSValueToObject(ctx, function, NULL);
    if (json != NULL) 
    {
        switch(arg_type) 
        {
            case kJSTypeObject : 
                js_json = JSStringCreateWithUTF8CString(json);
                v = JSValueMakeFromJSONString(ctx, js_json);
                JSStringRelease(js_json);
                break;
            case kJSTypeString : 
                v = js_char_to_value(ctx, json);
                break;
            default : 
                break;
        }
    }
    if (v) 
    {
        JSValueRef vals[] = { v };
        js_ret = JSObjectCallAsFunction(ctx, function_object, NULL, 1, vals, NULL);
    }
    else 
        js_ret = JSObjectCallAsFunction(ctx, function_object, NULL, 0, NULL, NULL);
    
    if (char_ret != NULL) 
        ret = js_value_to_char(ctx, js_ret, JS_STRING_MAX, NULL);

error_out: 
    if (js_name)
        JSStringRelease(js_name);
    if (char_ret != NULL)
        *char_ret = ret;
    return ret;
}/*}}}*/

char *
js_value_to_string(JSContextRef ctx, JSValueRef value, size_t limit, JSValueRef *exc)
{
    JSStringRef jsstring = JSValueToStringCopy(ctx, value, exc);
    if (jsstring == NULL) 
        return NULL;

    char *ret = js_string_to_char(ctx, jsstring, limit);
    JSStringRelease(jsstring);
    return ret;
}
/*{{{*/
char *
js_value_to_char(JSContextRef ctx, JSValueRef value, size_t limit, JSValueRef *exc) 
{
    if (value == NULL)
        return NULL;
    if (! JSValueIsString(ctx, value)) 
        return NULL;
    return js_value_to_string(ctx, value, limit, exc);
}/*}}}*/

/* print_exception {{{*/
gboolean
js_print_exception(JSContextRef ctx, JSValueRef exception, char *buffer, size_t bufferSize, int starting_line, int *linenumber)
{
    if (exception == NULL) 
        return false;
    if (!JSValueIsObject(ctx, exception))
        return false;
    JSObjectRef o = JSValueToObject(ctx, exception, NULL);
    if (o == NULL) 
        return false;

    gint line = (int)js_get_double_property(ctx, o, "line");
    gchar *message = js_get_string_property(ctx, o, "message");
    char *sourceURL = js_get_string_property(ctx, o, "sourceURL");
    if (sourceURL)
        fprintf(stderr, "DWB SCRIPT EXCEPTION: in file %s\n", sourceURL);
    fprintf(stderr, "DWB SCRIPT EXCEPTION: in line %d: %s\n", line + starting_line, message == NULL ? "unknown" : message);
    if (sourceURL != NULL && buffer != NULL)
    {
        strncpy(buffer, message, bufferSize-1);
        buffer[bufferSize-1] = '\0';
    }
    if (linenumber)
        *linenumber = line;
    g_free(message);
    g_free(sourceURL);
    return true;
}
/*}}}*/


JSObjectRef  
js_make_function(JSContextRef ctx, const char *script, const char *sourceurl, int linenumber) 
{
    JSValueRef exc;
    JSObjectRef ret = NULL;
    JSStringRef body = JSStringCreateWithUTF8CString(script);
    JSStringRef source = NULL;
    if (sourceurl)
        JSStringCreateWithUTF8CString(sourceurl);

    JSObjectRef function = JSObjectMakeFunction(ctx, NULL, 0, NULL, body, source, linenumber, &exc);
    if (function != NULL) 
        ret = function;
    else 
        js_print_exception(ctx, exc, NULL, 0, 0, NULL);

    JSStringRelease(body);
    if (source != NULL)
        JSStringRelease(source);
    return ret;
}

char *
js_value_to_json(JSContextRef ctx, JSValueRef value, size_t limit, int indent, JSValueRef *exc) 
{
    if (value == NULL)
        return NULL;
    JSStringRef js_json = JSValueCreateJSONString(ctx, value, indent, exc);
    if (js_json == NULL)
        return NULL;
    char *json = js_string_to_char(ctx, js_json, limit);
    JSStringRelease(js_json);
    return json;
}

JSValueRef 
js_json_to_value(JSContextRef ctx, const char *text) 
{
    JSStringRef json = JSStringCreateWithUTF8CString(text == NULL || *text == 0 ? "{}" : text);
    JSValueRef ret = JSValueMakeFromJSONString(ctx, json);
    JSStringRelease(json);
    return ret;
}
JSValueRef
js_execute(JSContextRef ctx, const char *script, JSValueRef *exc) 
{
    JSObjectRef function = js_make_function(ctx, script, NULL, 0);
    if (function != NULL) 
        return JSObjectCallAsFunction(ctx, function, function, 0, NULL, exc); 
    
    return NULL;
}
void 
js_array_iterator_init(JSContextRef ctx, js_array_iterator *iter, JSObjectRef object) 
{
    g_return_if_fail(ctx != NULL && object != NULL);
    iter->ctx = ctx;

    iter->array = object;
    JSValueProtect(ctx, iter->array);

    iter->current_index = 0;
    double length = js_get_double_property(ctx, object, "length");
    iter->length = isnan(length) ? -1 : (int) length;
}
JSValueRef 
js_array_iterator_next(js_array_iterator *iter, JSValueRef *exc) 
{
    g_return_val_if_fail(iter != NULL && iter->array != NULL, NULL);

    if (iter->current_index < iter->length)
        return JSObjectGetPropertyAtIndex(iter->ctx, iter->array, iter->current_index++, exc);
    return NULL;
}
void 
js_array_iterator_finish(js_array_iterator *iter)
{
    g_return_if_fail(iter != NULL && iter != NULL && iter->array != NULL);

    JSValueUnprotect(iter->ctx, iter->array);
}
void 
js_property_iterator_init(JSContextRef ctx, js_property_iterator *iter, JSObjectRef object) 
{
    iter->ctx = ctx;

    iter->array = JSObjectCopyPropertyNames(ctx, object);
    JSPropertyNameArrayRetain(iter->array);

    iter->object = object;
    JSValueProtect(ctx, object);

    iter->current_index = 0;
    iter->length = JSPropertyNameArrayGetCount(iter->array);
}

JSValueRef 
js_property_iterator_next(js_property_iterator *iter, JSStringRef *jsname_ret, char **name_ret, JSValueRef *exc) 
{
    g_return_val_if_fail(iter != NULL && iter->array != NULL, NULL);

    if (iter->current_index < iter->length)
    {
        JSStringRef js_name = JSPropertyNameArrayGetNameAtIndex(iter->array, iter->current_index++);
        JSValueRef ret = JSObjectGetProperty(iter->ctx, iter->object, js_name, exc);

        if (name_ret)
            *name_ret = js_string_to_char(iter->ctx, js_name, -1);

        if (jsname_ret)
            *jsname_ret = js_name;
        else 
            JSStringRelease(js_name);
        return ret;
    }

    if (name_ret)
        *name_ret = NULL;
    return NULL;
}
void 
js_property_iterator_finish(js_property_iterator *iter)
{
    g_return_if_fail(iter != NULL);

    if (iter->array)
        JSPropertyNameArrayRelease(iter->array);

    if (iter->object)
        JSValueUnprotect(iter->ctx, iter->object);
}

JSObjectRef 
js_value_to_function(JSContextRef ctx, JSValueRef val, JSValueRef *exc)
{
    JSObjectRef ret = JSValueToObject(ctx, val, exc);
    if (ret != NULL && JSObjectIsFunction(ctx, ret))
        return ret;
    return NULL;
}
void *
js_get_private(JSContextRef ctx, JSValueRef v, JSValueRef *exc) {
    JSObjectRef o = JSValueToObject(ctx, v, exc);
    if (o != NULL) {
        return JSObjectGetPrivate(o);
    }
    return NULL;
}

gboolean 
js_check_syntax(JSContextRef ctx, const char *script, const char *filename, int lineOffset)
{
    JSValueRef exc = NULL;
    JSStringRef jsscript = JSStringCreateWithUTF8CString(script);
    JSStringRef jssource = NULL; 
    if (filename != NULL)
        jssource = JSStringCreateWithUTF8CString(filename);

    gboolean correct = JSCheckScriptSyntax(ctx, jsscript, jssource, lineOffset, &exc);
    if (!correct)
    {
        js_print_exception(ctx, exc, NULL, 0, 0, NULL);
    }
    JSStringRelease(jsscript);
    if (jssource != NULL)
        JSStringRelease(jssource);

    return correct;
}

