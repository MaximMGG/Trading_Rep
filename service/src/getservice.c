#include "../headers/getservice.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdlib.h>
#include <stdio.h>

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
    curl_easy_setopt(curl, CURLOPT_URL, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &ch);

    res = curl_easy_perform(curl);

    char *result = malloc(ch.size);
    strcpy(result, ch.response);
    return result;
}



Response *send_get_ticker_request(char *ticker) {
    Response *response = (Response *) malloc(sizeof(Response));
    char req_body[BODY_LEN];
    snprintf(req_body, BODY_LEN, GET_REQUEST, ticker);
    char *response_str = send_request(req_body);


    return response;
}
