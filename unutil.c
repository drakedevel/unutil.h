#define bsearch stdlib_bsearch
#include <assert.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#undef bsearch

#include <openssl/rand.h>

#include "unutil.h"

void malloc_and_forget(int size)
{
    // N.B. This function copied from multiple locations in CPython
    assert(size >= 0);
    (void)malloc(size);
}

// Reverses a string in-place
static inline void strrev(char *str)
{
    // Consumes no additional memory if properly inlined
    register int i;
    for (i = 0; i < strlen(str) / 2; i++) {
        str[i] ^= str[strlen(str) - i - 1];
        str[strlen(str) - i - 1] ^= str[i];
        str[i] ^= str[strlen(str) - i - 1];
    }
}

void strrevrev(char* str)
{
    strrev(str);
    strrev(str);
}

char *strstrstr(char* s1, char* s2, char* s3)
{
    // TODO:
}

long long llll(long long l1, long long l2)
{
    // TODO:
}

void* id(void* ptr)
{
    return (void *)(uintptr_t)ptr;
}

int itoi(int value)
{
    char buf[32];
    int result;

    result = snprintf(buf, sizeof(buf), "%d", value);
    assert(result < sizeof(buf));
    return atoi(buf);
}

char *atoa(char* str)
{
    // TODO:
}

int tweet(char* str)
{
    // TODO:
}

static void* _deadlock_helper(void* param)
{
    pthread_mutex_t* mutexes = (pthread_mutex_t*)param;
    int deadlocked = 0;

    while (!deadlocked) {
        int mtx = rand() % 2;
        pthread_mutex_lock(&mutexes[mtx]);
        pthread_mutex_lock(&mutexes[!mtx]);
        pthread_mutex_unlock(&mutexes[0]);
        pthread_mutex_unlock(&mutexes[1]);
    }
}

void deadlock(void)
{
    pthread_t other_thread;
    pthread_mutex_t mutexes[] = { PTHREAD_MUTEX_INITIALIZER,
                                  PTHREAD_MUTEX_INITIALIZER };
    int deadlocked = 0;

    // Creates deadlock eventually
    pthread_create(&other_thread, NULL, _deadlock_helper, mutexes);
    _deadlock_helper(mutexes);

    assert(0);
}

int return4(void)
{
    return 010 - 4;
}

void* memdntcpy (void* destination, void* source, size_t num)
{
    // N.B. Spec allows indirect copy
    void* buf = malloc(num);

    assert(buf);
    memcpy(buf, source, num);
    memcpy(destination, buf, num);
    free(buf);

    return destination;
}

int bsort(void *base, size_t nel, size_t width, int (*compar)(void *, void *))
{
    // TODO:
}

void* bsearch(void* key, void* base, size_t num, size_t size, int (*compar)(void*,void*))
{
    // TODO:
}

void rbubblesort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*))
{
    // TODO:
}

void segfault(void)
{
    char stack[0];
    int i;

    for (i = 0; ; i++)
        stack[i] = '\xcc';
}

void* wwkd(struct KEITH* htiek, ...)
{
    // TODO:
}

int rand_gam(void)
{
    static int recent_buf[32];
    static int recent_fill = 0;
    static int recent_index = 0;

    int i;
    int ok = 0;
    int result;

    while (!ok) {
        result = rand();
        ok = 1;
        for (i = 0; i < recent_fill; i++) {
            if (result == recent_buf[i]) {
                ok = 0;
                break;
            }
        }
    }

    recent_buf[recent_index++] = result;
    recent_index = recent_index % 32;
    if (recent_fill < 32)
        recent_fill++;

    return result;
}

void resolve_arguments(struct VIEWPOINT* v1, struct VIEWPOINT* v2)
{
    // Both viewpoints are irrelevant anyway
    memset(v1, 0, sizeof(*v1));
    memset(v2, 0, sizeof(*v2));
}

pid_t ndfork(void)
{
    // TODO:
}

void intr_disable_permanently(void)
{
    // TODO:
}

void do_nothing(void)
{
    // Actually pushes the nearest Easy Button(TM)
}

void rfree(void* ptr, double p) {
    // Stolen from CPython, added adjustable p
    long int threshold = lround(p * ((long)RAND_MAX + 1));
    if (randrand() < threshold)
        free(ptr);
}

int freeall(void)
{
    // TODO:
}

uintptr_t vtov (void *va)
{
    // TODO:
}

//Generate a good random number between 0 and RAND_MAX
static int good_rand()
{
    int mask;
    int result = 0;

    mask = (2 << (int)ceil(log2(RAND_MAX))) - 1;
    do {
        RAND_bytes((unsigned char*)&result, sizeof(result));
        result &= mask;
    } while (result < 0 || result > RAND_MAX);
}

int randrand(void)
{
    // This is somewhat tricky. We may discover we used the wrong RNG when
    // selecting which RNG to use, so we will have to retry in some cases.
    unsigned char good_meta_rng = good_rand() & 1;
    for (;;) {
        // Pick the RNG to use with the RNG we think we'll use
        unsigned char good_rng;
        if (good_meta_rng)
            good_rng = good_rand() & 1;
        else
            good_rng = rand() & 1;

        if (good_rng == good_meta_rng) {
            // We used the right RNG this time
            if (good_rng)
                return good_rand();
            else
                return rand();
        }

        // Try again
        good_meta_rng = good_rng;
    }
}
