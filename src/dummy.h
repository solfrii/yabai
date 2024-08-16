//
//  dummy.h
//  yabai
//
//  Created by DD on 15.08.2024.
//

#ifndef dummy_h
#define dummy_h

void dummy_plog(void *proc, const char* format, ...);
void dummy_alog(void *app,  const char* format, ...);
void dummy_wlog(void *win,  const char* format, ...);

void dummy_flog(const char * format, ...);

#endif /* dummy_h */
