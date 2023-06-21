#include "search_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// This function should loop over the vocabulary (which contains num_words
// entries) and return the number of words in which that particular letter
// occurs. So if there are 15 words containing the letter 'x' for the particular
// vocabulary, then this function will return 15.
int score_letter(char letter, char** vocabulary, size_t num_words) {
    int letterScore = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (vocabulary[i] != NULL) {
            if (strchr(vocabulary[i], letter) != NULL) {
                letterScore++;
            }
        }
        
    }

    return letterScore;
    // TODO(you): implement this function!
    return 0;

}


// Calculate the score for a given word, where the letter_scores array has
// already been filled out for you and is guaranteed to be of length 26. Slot 0
// contains the score for 'a', and slot 25 contains the score for 'z'.
// The score for a word is the sum of all of the letter scores, *for unique
// letters*. So if the letter 'e' occurs three times, it only contributes to the
// score once.
int score_word(char *word, int *letter_scores) {
    int result = 0;

    char* letterList = calloc(5, sizeof(char));
    for (int x = 0; x < 5; x++) {
        if (!strchr(letterList, word[x])) {
            strncat(letterList, word + x, 1);
        }

        
    }
    int dur = strlen(letterList);
    for (int j = 0; j < dur; j++) {
        char cur = letterList[j];
        int thing = cur - 'a';
        result = result + letter_scores[thing];
    }
    //char* letterList[5];
    //This should return the sum of the letter score on all the letters on the word example:
    //score i = 1, score r = 1, score a = 1, score t = 1, score e = 1. score of irate = 5
    // Got a stupid idea, go though every index of word, check if we've seen this char yet, if so not it to a seen before var, if we have just move to the next.
    // After we check every index we then try ascribe the letter_score index to each unique char we saved. Return sum of that. I hate this idea it's so incredibly stupid. 
    //for (int i = 0; i < 5; i++) {
    //    if (strchr(letterList, word[i]) == NULL) {
    //        letterList[i] = word[i];
     //   }
      //  else {
        //    letterList[i] = ' ';
       // }
    //}

    //int dur = strlen(letterList);

    //for (int j = 0; j < dur; j++) {
    //    char cur = letterList[j];
     //   if(cur != ' '){
     //       int thing = cur - 'a';
     //       result = result + letter_scores[thing];
      //  }
    //}
    free(letterList);
    return result;
  // TODO(you): implement this function!
  return 0;

}

// Returns the optimum guess, based on our heuristic.
// This one works, you don't have to change it.
// Note that this function allocates a new string every time it runs, and those
// strings will need to be freed!
char* get_guess(char** vocabulary, size_t num_words) {
    int letter_scores[26];

    for (int i = 0; i < 26; i++) {
        letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
    }

    char* best_guess = NULL;
    int best_score = 0;
    int score = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (vocabulary[i] == NULL) {
            continue;
        }
        score = score_word(vocabulary[i], letter_scores);
        if (score > best_score) {
            best_guess = vocabulary[i];
            best_score = score;
        }
    }
    return best_guess ? strdup(best_guess) : NULL;
}


// This function will filter down the vocabulary based on the knowledge that the
// specified letter *does not occur* in the secret word. So for any of the words
// in the vocabulary that do contain that letter, free their pointers and set
// the corresponding slot to NULL.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_gray(char letter, char **vocabulary,
                              size_t num_words) {
    size_t grays = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (vocabulary[i] != NULL) {
            if (strchr(vocabulary[i], letter) != NULL) {
                free(vocabulary[i]);
                vocabulary[i] = NULL;
                grays++;
            }
        }
        
    }
    return grays;
  // TODO(you): implement this function!
  return 0;

}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter occurs in the word, *but not at this particular position*.
// So remove any words that either don't contain the letter at all, or do
// contain it, but at the specified position.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_yellow(char letter, int position, char** vocabulary,
    size_t num_words) {
    size_t yellow = 0;

    for (size_t i = 0; i < num_words; i++) {

        if (vocabulary[i] != NULL) {
            if (strchr(vocabulary[i], letter) == NULL) {
                free(vocabulary[i]);
                vocabulary[i] = NULL;
                yellow++;
            }
            else if (strchr(vocabulary[i], letter) && vocabulary[i][position] == letter) {
                free(vocabulary[i]);
                vocabulary[i] = NULL;
                yellow++;
            }
        }
    }
    return yellow;
        

    // TODO(you): implement this function!
    return 0;

}


// This function will filter down the vocabulary based on the knowledge that the
// specified letter *definitely* occurs as the specified position. So remove any
// word that does not contain, for the specified position, the specified letter.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_green(char letter, int position, char **vocabulary,
                               size_t num_words) {

    size_t greens = 0;
    for (size_t i = 0; i < num_words; i++) {
        if(vocabulary[i] != NULL){
            if (vocabulary[i][position] != letter) {
                free(vocabulary[i]);
                vocabulary[i] = NULL;
                greens++;
            }
        }
    }
    return greens;

  // TODO(you): implement this function!
  return 0;

}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
