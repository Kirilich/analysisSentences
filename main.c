#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SENTENCES 300
#define MAX_LENGTH 1000

int multipleUppercase (const char *sentence) {
    int capital_count = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (isupper(sentence[i])) {
            capital_count++;
            if (capital_count > 1) {
                return 1;
            }
        }
    }
    return 0;
}

void removeWhitespace (char *sentence) {
    int i = 0;
    while (sentence[i] == ' ' || sentence[i] == '\t') {
        i++;
    }
    memmove(sentence, sentence + i, strlen(sentence + i) + 1);
}

int main() {
    char input[MAX_LENGTH];
    char sentences[MAX_SENTENCES][MAX_LENGTH];
    int sentenceCount = 0;
    int formattedCount = 0;
    fgets(input, MAX_LENGTH, stdin);
    char *start = input;
    while (*start) {
        char *end = strpbrk(start, ".;?");
        if (!end) break;
        int length = end - start + 1;
        strncpy(sentences[sentenceCount], start, length);
        sentences[sentenceCount][length] = '\0';
        removeWhitespace(sentences[sentenceCount]);
        if (strstr(sentences[sentenceCount], "Dragon flew away!") != NULL) {
            break;
        }
        sentenceCount++;
        start = end + 1;
    }
    for (int i = 0; i < sentenceCount; i++) {
        if (!multipleUppercase(sentences[i])) {
            printf("%s\n", sentences[i]);
            formattedCount++;
        }
    }
    printf("Количество предложений до %d и количество предложений после %d\n", sentenceCount, formattedCount);
    return 0;
}
