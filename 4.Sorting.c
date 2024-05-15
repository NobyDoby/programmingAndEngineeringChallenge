#include <libpynq.h>
#include <stdio.h>
#include <string.h>

#define MAX_DISPLAY 240
#define MAXPERSONS MAX_DISPLAY
#define MAXNAME 100
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 240

struct person_t
{
  char name[MAXNAME];
  float height;
};

int swappedIndex = -1;
int highlightIndex1 = -1;
int highlightIndex2 = -1;

int initialise(struct person_t persons[], int nrPersons);
void printValues(struct person_t persons[], int from, int to);
float maxValue(struct person_t persons[], int nrPersons);
float minValue(struct person_t persons[], int nrPersons);
void replacePerson(struct person_t persons[], int nrPersons);
void bubbleSort(struct person_t persons[], int nrPersons);
void mrgeSort(struct person_t persons[], int nrPersons, int left, int right);
void merge(struct person_t a[], int left, int mid, int right);
void displayValues(display_t display, struct person_t persons[], int nrPersons, int from, int to);

int main(void)
{
  pynq_init();
  display_t display;
  display_init(&display);
  char cmd;
  int nrPersons;

  struct person_t persons[MAXPERSONS];
  while (1)
  {
    printf("Command? ");
    scanf(" %c", &cmd);
    switch (cmd)
    {
    case 'm':
      mrgeSort(persons, nrPersons, 0, nrPersons - 1);
      break;
    case 'b':
      bubbleSort(persons, nrPersons);
      break;
    case 'd':
      if (nrPersons == 0)
      {
        break;
      }
      else
      {
        displayValues(display, persons, nrPersons, -1, -1);
      }
      break;
    case 'r':
      replacePerson(persons, nrPersons);
      break;
    case 'h':
      float a = 0, b = 0;
      a = maxValue(persons, nrPersons);
      b = minValue(persons, nrPersons);
      if (b > 100000)
      {
        b = 0;
      }

      printf("Min: %.3f\n", b);
      printf("Max: %.3f\n", a);
      printf("Range: %.3f\n", a - b);
      break;
    case 'p':
      int from = 0;
      int to = nrPersons;
      printValues(persons, from, to);
      break;
    case 'i':
      printf("Number of persons? ");
      scanf("%d", &nrPersons);
      nrPersons = initialise(persons, nrPersons);
      break;
    case 'q':
      printf("Bye!\n");
      return 0;
      break;

    default:
      printf("Unknown command '%c'\n", cmd);
      break;
    }
  }

  display_destroy(&display);
  pynq_destroy();
}

int initialise(struct person_t persons[], int nrPersons)
{

  while (nrPersons < 1 || nrPersons > 240)
  {
    printf("Number of persons must be from 1 up to 240\n");
    scanf("%d", &nrPersons);
    return 0;
  }
  int k = nrPersons;
  for (int i = 0; i < nrPersons; i++)
  {
    sprintf(persons[i].name, "person-%d", i);
    k--;
    persons[i].height = k;
  }
  return nrPersons;
}

void printValues(struct person_t persons[], int from, int to)
{

  printf("[");
  for (int i = from; i < to; i++)
  {
    if (i == to - 1)
    {
      printf("(\"%s\",%.2lf)", persons[i].name, persons[i].height);
    }
    else
    {
      printf("(\"%s\",%.2lf),", persons[i].name, persons[i].height);
    }
  }
  printf("]\n");
}

float maxValue(struct person_t persons[], int nrPersons)
{
  float maxim = 0;

  for (int i = 0; i < nrPersons; i++)
  {
    if (persons[i].height >= maxim)
    {
      maxim = (float)persons[i].height;
    }
  }
  return maxim;
}
float minValue(struct person_t persons[], int nrPersons)
{
  float minim = 100000000;

  for (int i = 0; i < nrPersons; i++)
  {
    if (persons[i].height < minim)
    {
      minim = (float)persons[i].height;
    }
  }
  return minim;
}

void replacePerson(struct person_t persons[], int nrPersons)
{
  int i;
  char nume[MAXNAME];
  float inaltime = 0;

  printf("Index? ");
  scanf("%d", &i);
  if (i < 0 || i >= nrPersons)
  {
    printf("Error: Invalid index!\n");
  }
  else
  {
    printf("Name? ");
    scanf("%s", nume);
    strcpy(persons[i].name, nume);
    printf("Height? ");
    scanf("%f", &inaltime);
    persons[i].height = inaltime;
  }
}

void bubbleSort(struct person_t persons[], int nrPersons)
{
  int i, j;
  struct person_t k;
  display_t display;
  display_init(&display);
  displayFillScreen(&display, RGB_BLACK);
  for (j = 0; j < nrPersons - 1; j++)
  {
    for (i = 0; i < nrPersons - j - 1; i++)
    {
      if (persons[i].height > persons[i + 1].height)
      {
        k = persons[i + 1];
        persons[i + 1] = persons[i];
        persons[i] = k;
        printf("after swapping: ");
        printValues(persons, 0, nrPersons);
        displayValues(display, persons, nrPersons, swappedIndex, swappedIndex + 1);
      }
      else if (persons[i].height == persons[i + 1].height)
      {
        if (strcmp(persons[i].name, persons[i + 1].name) > 0)
        {
          k = persons[i + 1];
          persons[i + 1] = persons[i];
          persons[i] = k;
          printf("after swapping: ");
          printValues(persons, 0, nrPersons);
          displayValues(display, persons, nrPersons, swappedIndex, swappedIndex + 1);
        }
      }
    }
  }
}

void mrgeSort(struct person_t persons[], int nrPersons, int left, int right)
{
  display_t display;
  display_init(&display);
  displayFillScreen(&display, RGB_BLACK);
  int mid = (left + right) / 2;
  if (left < right)
  {
    if (left != right)
    {
      printf("need to sort      ");
      printValues(persons, left, right + 1);
      displayValues(display, persons, nrPersons, left, right+1);

    }

    mrgeSort(persons, nrPersons, left, mid);
    printf("after sorting lhs ");
    printValues(persons, left, mid + 1);
    displayValues(display, persons, nrPersons, left, mid+1);


    mrgeSort(persons, nrPersons, mid + 1, right);
    printf("after sorting rhs ");
    printValues(persons, mid + 1, right + 1);
    displayValues(display, persons, nrPersons, mid, right+1);


    merge(persons, left, mid, right);
    printf("after merging     ");
    printValues(persons, left, right + 1);
    displayValues(display, persons, nrPersons, left, right+1);

  }
}

void merge(struct person_t persons[], int left, int mid, int right)
{
  struct person_t tmp[right - left + 1];
  int pos = 0;
  int lpos = left;
  int rpos = mid + 1;
  while (lpos <= mid && rpos <= right)
  {
    if (persons[lpos].height != persons[rpos].height)
    {
      if (persons[lpos].height < persons[rpos].height)
      {
        tmp[pos] = persons[lpos];
        pos++;
        lpos++;
      }
      else
      {
        tmp[pos] = persons[rpos];
        pos++;
        rpos++;
      }
    }
    else if (persons[lpos].height == persons[rpos].height)
    {
      if (strcmp(persons[lpos].name, persons[rpos].name) < 1)
      {
        tmp[pos] = persons[lpos];
        pos++;
        lpos++;
      }
      else
      {
        tmp[pos] = persons[rpos];
        pos++;
        rpos++;
      }
    }
  }
  while (lpos <= mid)
    tmp[pos++] = persons[lpos++];
  while (rpos <= right)
    tmp[pos++] = persons[rpos++];
  for (int i = 0; i < pos; i++)
    persons[i + left] = tmp[i];
}

void displayValues(display_t display, struct person_t persons[], int nrPersons, int from, int to) {
    if (nrPersons == 0) return;  

    float min = minValue(persons, nrPersons);
    float range = maxValue(persons, nrPersons) - min;
    float scale = (DISPLAY_HEIGHT - 1) / range; 

    displayFillScreen(&display, rgb_conv(0, 0, 255));

    for (int i = 0; i < nrPersons; i++) {
        int barWidth = DISPLAY_WIDTH / nrPersons;

        int barHeight;
        if (nrPersons == 1) {
            barHeight = persons[i].height * scale;
        } else {
            barHeight = (persons[i].height - min) * scale + 1;
        }
        int xStart = i * barWidth;
        int xEnd = xStart + barWidth;
        int barColor;
        if (i >= from && i <= to) {
            barColor = RGB_RED;
        } else if (i == highlightIndex1 || i == highlightIndex2) {
            barColor = RGB_RED;
        } else {
            barColor = RGB_GREEN;
        }

        xStart = (xStart < 0) ? 0 : xStart;
        xEnd = (xEnd > DISPLAY_WIDTH - 1) ? DISPLAY_WIDTH - 1 : xEnd;
        barHeight = (barHeight < 0) ? 0 : barHeight;

        displayDrawFillRect(&display, xStart, DISPLAY_HEIGHT - barHeight, xEnd, DISPLAY_HEIGHT - 1, barColor);
        sleep_msec(200);
    }
}
