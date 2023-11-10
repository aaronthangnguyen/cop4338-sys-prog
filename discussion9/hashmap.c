#include "hash.h"

hashmap hash_init(void)
{
    hashmap h = {(map_node **)malloc(BINS * sizeof(map_node *)), 0, BINS};
    for (int i = 0; i < BINS; i++)
        h.table[i] = NULL;
    return h;
}
static int hash(char *key, int bins)
{
    unsigned hashval = 0;
    for (int i = 0; i < strlen(key); i++)
        hashval = 31 * hashval + key[i];
    return hashval % bins;
}
static void rehash(hashmap *);
int contains_key(hashmap h, char *key)
{
    int index = hash(key, h.bins);
    for (map_node *iterator = h.table[index]; iterator; iterator = iterator->next)
        if (!strcmp(iterator->key, key))
            return 1;
    return 0;
}
int put(hashmap *h, char *key, int value)
{
    int index = hash(key, h->bins);
    for (map_node *iterator = h->table[index]; iterator; iterator = iterator->next)
        if (!strcmp(iterator->key, key))
        { // I found the key
            int old_val = iterator->value;
            iterator->value = value;
            return old_val; // return old value
        }
    if (h->size >= h->bins) // load factor >= 100%
        rehash(h);
    map_node *new_element = (map_node *)malloc(sizeof(map_node));
    new_element->next = h->table[index];
    new_element->key = strdup(key);
    new_element->value = value;
    h->table[index] = new_element;
    h->size++;
    return 0; // return old value
}
int get(hashmap h, char *key)
{
    int index = hash(key, h.bins);
    for (map_node *iterator = h.table[index]; iterator; iterator = iterator->next)
        if (!strcmp(iterator->key, key))
            return iterator->value;
    return 0;
}
char *to_str(hashmap h)
{
    char *rv = (char *)malloc(h.size * 100 + 1);
    for (int i = 0; i < h.bins; i++)
        for (map_node *it = h.table[i]; it; it = it->next)
            sprintf(rv, "%s\n%s: %d", rv, it->key, it->value);
    return rv;
}
static int next_prime(int min)
{ // next prime number greater than or equal to min
    while (1)
    {
        int prime = 1;
        for (int div = 2; div <= sqrt(min); div++)
            if (min % div == 0)
            {              // divisible by div
                prime = 0; // not prime
                break;
            }
        if (prime)
            return min;
        else
            min++;
    }
    return min;
}
static void rehash(hashmap *h)
{
    map_node **oldtable = h->table;
    int old_bins = h->bins;
    h->table = (map_node **)malloc(next_prime(2 * h->bins) * sizeof(map_node *));
    h->size = 0;
    h->bins = next_prime(2 * h->bins);
    for (int i = 0; i < old_bins; i++)
        for (map_node *it = oldtable[i]; it; it = it->next)
            put(h, it->key, it->value);
}