#include "hash.h"
#include <pthread.h>

#define error(m, c)             \
  do                            \
  {                             \
    fprintf(stderr, "%s\n", m); \
    exit(c);                    \
  } while (0)

hashset h;
char *words[100000];
static int N;
typedef struct
{
  int from_index;
  int to_index;
} producer_task;

static pthread_mutex_t mutex;

void *producer(void *args)
{
  producer_task *task = (producer_task *)args;
  for (int j = task->from_index; j <= task->to_index; j++)
  {
    pthread_mutex_lock(&mutex);
    insert(&h, words[j]);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

static int m; // number of consumer threads
static int k; // number of passwords that need to be generated by this program
static int l; // number of words per passwords

void *consumer(void *args)
{
  char password[25 * l];
  for (int i = 0; i < k / m; i++)
  {
    password[0] = '\0';
    for (int j = 0; j < l; j++)
    {
      char *random_word = words[rand() % N];
      pthread_mutex_lock(&mutex);
      int found = delete_value(&h, random_word);
      pthread_mutex_unlock(&mutex);
      if (found == 0)
      {
        j--;
        continue;
      }

      if (j == 0) // first word
        strcpy(password, random_word);
      else // first word
        sprintf(password, "%s,%s", password, random_word);
    }

    printf("%s\n", password);
  }
  return NULL;
}

int main(int argc, char **argv)
{
  srand(time(NULL));
  pthread_mutex_init(&mutex, NULL); // initializing the mutex for hash set
  int n;                            // number of producer threads
  char *file;                       // dictionary file (path) name (extension)
  if (argc != 11)
    error("fatal error: use the following CLAs: -p n -c m -f -n k file -l l",
          1);
  char *message = (char *)malloc(100);
  while (*++argv)
  {
    if (argv[0][0] != '-')
    {
      sprintf(message, "fatal error: illegal command-line detected: %s", *argv);
      error(message, 2);
    }
    switch (argv[0][1])
    {
    case 'p':
      sscanf(*(++argv), "%d", &n);
      break;
    case 'c':
      sscanf(*(++argv), "%d", &m);
      break;
    case 'l':
      sscanf(*(++argv), "%d", &l);
      break;
    case 'n':
      sscanf(*(++argv), "%d", &k);
      break;
    case 'f':
      file = (char *)malloc(100);
      sscanf(*(++argv), "%s", file);
      break;
    default:
      sprintf(message, "fatal error: flag -%c is not supported", argv[0][1]);
      error(message, 3);
    }
  }
  if (k % m)
    error("fatal error: requested number of passwords is not divisible by the "
          "given number of consumers",
          4);
  h = set_init();
  char word[500];
  FILE *f = fopen(file, "r");
  int i = 0;
  while (fgets(word, 500, f))
  {
    int n = strlen(word);
    if (!n)
      continue;
    if (word[n - 1] == '\n')
      word[n - 1] = '\0';
    words[i++] = strdup(word);
  }
  fclose(f);

  N = i; // # of words in dictionary!

  // PRODUCTION PHASE
  pthread_t producer_thread_id[n];
  producer_task tasks[n];

  for (int i = 0; i < n; i++)
  {
    tasks[i].from_index = i * (N / n);
    tasks[i].to_index = (i + 1) * (N / n) - 1;
    pthread_create(&producer_thread_id[i], NULL, producer, (void *)&tasks[i]);
  }

  for (int i = 0; i < n; i++)
    pthread_join(producer_thread_id[i], NULL);

  // CONSUMPTION PHASE
  pthread_t consumer_thread_id[m];

  for (int i = 0; i < m; i++)
    pthread_create(&consumer_thread_id[i], NULL, consumer, NULL);

  for (int i = 0; i < m; i++)
    pthread_join(consumer_thread_id[i], NULL);
  return 0;
}
