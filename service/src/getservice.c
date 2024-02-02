#include "../headers/getservice.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/pr_map.h>

#define BODY_LEN 128

struct mem {
    char *response;
    size_t size;
};

static size_t write_func(void *data, size_t size, size_t nmemb, void *clientp) {
    size_t realsize = size * nmemb;
    struct mem *m = (struct mem *) clientp;

    char *ptr = realloc(m->response, m->size + realsize + 1);
    tryp(ptr);
    m->response = ptr;
    memcpy(&(m->response[m->size]), data, realsize);
    m->size += realsize;
    m->response[m->size] = '\0';

    return realsize;
}

static char *send_request(char *request) {
    struct mem ch = {0};
    CURLcode res;
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, request);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &ch);

    res = curl_easy_perform(curl);
    if (res != 0) {
        fprintf(stderr, "Perform error %s\n", curl_easy_strerror(res));
    }

    char *result = malloc(ch.size);
    strcpy(result, ch.response);
    return result;
}

static Res_ticker *map_property_to_ticker(Property **prop, Res_ticker *res) {
    res->symbol = (char *) malloc(sizeof(prop[0]->val));
    strcpy(res->symbol, prop[0]->val);
    res->priceChange = atof(prop[1]->val);
    res->priceChangePercent = atof(prop[2]->val);
    res->weightedAvgPrice = atof(prop[3]->val);
    res->openPrice = atof(prop[4]->val);
    res->highPrice = atof(prop[5]->val);
    res->lowPrice = atof(prop[6]->val);
    res->lastPrice = atof(prop[7]->val);
    res->volume = atof(prop[8]->val);
    res->quoteVolume = atof(prop[9]->val);
    res->openTime = atol(prop[10]->val);
    res->closeTime = atol(prop[11]->val);
    res->firstId = atol(prop[12]->val);
    res->lastId = atol(prop[13]->val);
    res->count = atol(prop[14]->val);
    return res;
}

Res_ticker *send_get_ticker_request(char *ticker) {
    Res_ticker *response = (Res_ticker *) malloc(sizeof(Res_ticker));
    tryp(response);

    char req_body[BODY_LEN];
    snprintf(req_body, BODY_LEN, GET_REQUEST, ticker);
    char *response_str = send_request(req_body);
    tryp(response_str);
    int size = 0;
    Property **pr = parse_get_response(response_str, &size);
    tryp(pr);
    response = map_property_to_ticker(pr, response);

    free_property(pr, size);
    free(response_str);

    return response;
}

