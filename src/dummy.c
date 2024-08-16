//
//  dummy.c
//  yabai
//
//  Created by DD on 15.08.2024.
//

#include "dummy.h"

regex_t* get_name_filter(void) {
    const char* pattern = "(Calendar|.*)";
    
    static regex_t app_regex;
    static bool is_initialized = false;
    
    if (!is_initialized) {
        regcomp(&app_regex, pattern, REG_EXTENDED);
    }
    return &app_regex;
}

int get_counter(void) {
    static int counter = 0;
    ++counter;
    return counter;
}


void dummy_plog(void *_proc, const char* format, ...) {
    if (!_proc) return;
    
    struct process *proc = (struct process *) _proc;
    char* proc_name = proc->name;
    uint32 proc_id = proc->psn.lowLongOfPSN;
    
    regex_t* app_name_filter = get_name_filter();
    if (regex_match(true, app_name_filter, proc_name) == REGEX_MATCH_NO) {
//        printf("- <%s %i>\n", proc_name, proc_id);
        return;
    }
    
    va_list args;
    va_start(args, format);
    printf("+%.2i <%-10s %-7i>: ", get_counter(), proc_name, proc_id);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}


void dummy_alog(void *_app, const char* format, ...) {
    if (!_app) return;
    
    struct application *app = (struct application *) _app;
    char* app_name = app->name;
    
    regex_t* app_name_filter = get_name_filter();
    if (regex_match(true, app_name_filter, app_name) == REGEX_MATCH_NO) {
        printf("- [%s]\n", app_name);
        return;
    }
    
    va_list args;
    va_start(args, format);
    printf("+%.2i [%-10s]: ", get_counter(), app_name);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}


void dummy_wlog(void *_win, const char* format, ...) {
    if (!_win) return;
    
    struct window *win = (struct window *) _win;
    char* app_name = win->application->name;
    
    regex_t* app_name_filter = get_name_filter();
    if (regex_match(true, app_name_filter, app_name) == REGEX_MATCH_NO) {
//        printf("- [%-10s %-4i]\n", app_name, win->id);
        return;
    }
    
    va_list args;
    va_start(args, format);
    printf("+%.2i [%-10s %-4i]: ", get_counter(), app_name, win->id);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}


void dummy_flog(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("=== ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}
