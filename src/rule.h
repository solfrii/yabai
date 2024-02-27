#ifndef RULE_H
#define RULE_H

#define RULE_PROP_UD  0
#define RULE_PROP_ON  1
#define RULE_PROP_OFF 2

#define rule_check_flag(r, x) ((r)->flags  &  (x))
#define rule_clear_flag(r, x) ((r)->flags &= ~(x))
#define rule_set_flag(r, x)   ((r)->flags |=  (x))

enum rule_flags
{
    RULE_APP_VALID       = 1 <<  0,
    RULE_TITLE_VALID     = 1 <<  1,
    RULE_ROLE_VALID      = 1 <<  2,
    RULE_SUBROLE_VALID   = 1 <<  3,
    RULE_APP_EXCLUDE     = 1 <<  4,
    RULE_TITLE_EXCLUDE   = 1 <<  5,
    RULE_ROLE_EXCLUDE    = 1 <<  6,
    RULE_SUBROLE_EXCLUDE = 1 <<  7,
    RULE_FOLLOW_SPACE    = 1 <<  8,
    RULE_OPACITY         = 1 <<  9,
    RULE_LAYER           = 1 << 10,
    RULE_ONE_SHOT        = 1 << 11,
    RULE_ONE_SHOT_REMOVE = 1 << 12
};

struct rule
{
    char *label;
    char *app;
    char *title;
    char *role;
    char *subrole;
    regex_t app_regex;
    regex_t title_regex;
    regex_t role_regex;
    regex_t subrole_regex;
    uint32_t did;
    uint64_t sid;
    float opacity;
    int manage;
    int sticky;
    int mff;
    int layer;
    int fullscreen;
    unsigned grid[6];
    uint32_t flags;
};

void rule_serialize(FILE *rsp, struct rule *rule, int index);
void rule_reapply_all(void);
bool rule_reapply_by_index(int index);
bool rule_reapply_by_label(char *label);
void rule_apply(struct rule *rule);
void rule_add(struct rule *rule);
bool rule_remove_by_index(int index);
bool rule_remove_by_label(char *label);
void rule_destroy(struct rule *rule);

#endif
