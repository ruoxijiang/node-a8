//
// Created by weicheng qian on 2020/4/1.
//

#ifndef A8_ADNS_EDISON_H
#define A8_ADNS_EDISON_H
struct EdisonDNS {
    char *cname;
    char *record;
    char *domain;
    char *type;
    struct EdisonDNS *next;
};
#endif //A8_ADNS_EDISON_H
