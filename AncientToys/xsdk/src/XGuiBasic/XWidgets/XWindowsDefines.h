#pragma once

#define X_DECLARE_HANDLE(name) struct name##__; typedef struct name##__ *name

X_DECLARE_HANDLE(HINSTANCE);
