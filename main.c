#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

int countUppercase(const char *str) {
    int count = 0;
    while (*str) {
        if (isupper(*str)) count++;
        str++;
    }
    return count;
}

void removeTrailingWhitespace(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t')) {
        str[len - 1] = '\0';
        len--;
    }
}
char *removeWhitespace(char *str) {
    while (*str == ' ' || *str == '\t') str++;
    return str;
}

int main() {
    char *text = NULL;
    size_t size = 0;
    ssize_t bytesRead = getline(&text, &size, stdin);
    if (bytesRead == -1) {
        fprintf(stderr, "Ошибка чтения из файла.\n");
        return 1;
    }
    int originalCount = 0;
    int filteredCount = 0;
    size_t maxSentences = 10;
    char **filteredSentences = malloc(maxSentences * sizeof(char *));
    if (!filteredSentences) {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        free(text);
        return 1;
    }
    const char *ending_phrase = "Dragon flew away!";
    size_t text_len = strlen(text);
    if (text_len >= strlen(ending_phrase) && strstr(text + text_len - strlen(ending_phrase), ending_phrase)) {
        text[text_len - strlen(ending_phrase)] = '\0';
    }
    char *currentPosition = text;
    const char *delimiters = ".;?";
    while (*currentPosition) {
        size_t len = strcspn(currentPosition, delimiters);
        char ending_char = currentPosition[len];
        if (ending_char == '\0') break;
        char *sentence_start = removeWhitespace(currentPosition);
        char *sentence = malloc(len + 2);
        if (!sentence) {
            fprintf(stderr, "Ошибка выделения памяти для предложения.\n");
            free(sentence);
            break;
        }
        strncpy(sentence, sentence_start, len);
        sentence[len] = '\0'; 
        removeTrailingWhitespace(sentence);
        originalCount++;
        if (countUppercase(sentence) <= 1) {
            if (filteredCount >= maxSentences) {
                maxSentences *= 2;
                char **new_array = realloc(filteredSentences, maxSentences * sizeof(char *));
                if (!new_array) {
                    fprintf(stderr, "Ошибка увеличения памяти для массива предложений.\n");
                    free(sentence);
                    break;
                }
                filteredSentences = new_array;
            }
            filteredSentences[filteredCount] = sentence;
            filteredCount++;
        } else {
            printf("%d\n", countUppercase(sentence));
            printf(sentence);
            free(sentence);
        }
        currentPosition += len + 1;
    }
    for (int i = 0; i < filteredCount; i++) {
        printf("%s\n", filteredSentences[i]);
        free(filteredSentences[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", originalCount, filteredCount);
    free(filteredSentences);
    free(text);
    return 0;
}
