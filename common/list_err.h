#pragma once

class list_err {
public:
    const char *description;
    list_err(const char *s) { description = s; }
};
