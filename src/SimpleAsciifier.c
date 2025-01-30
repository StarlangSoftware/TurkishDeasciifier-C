//
// Created by Olcay Taner YILDIZ on 18.11.2023.
//

#include "SimpleAsciifier.h"

/**
 * The asciify method takes a Word as an input and converts it to a char array. Then,
 * loops i times, where i ranges from 0 to length of the char array and substitutes Turkish
 * characters with their corresponding Latin versions and returns it as a new String.
 *
 * @param word Word type input to asciify.
 * @return String output which is asciified.
 */
char *asciify_word(const char* word) {
    String_ptr modified = create_string();
    Array_list_ptr chars = all_characters(word);
    for (int i = 0; i < word_size(word); i++) {
        String_ptr ch = array_list_get(chars, i);
        if (string_equals2(ch, "ç")){
            string_append(modified, "c");
        } else {
            if (string_equals2(ch, "ö")){
                string_append(modified, "o");
            } else {
                if (string_equals2(ch, "ğ")){
                    string_append(modified, "g");
                } else {
                    if (string_equals2(ch, "ü")){
                        string_append(modified, "u");
                    } else {
                        if (string_equals2(ch, "ş")){
                            string_append(modified, "s");
                        } else {
                            if (string_equals2(ch, "ı")){
                                string_append(modified, "i");
                            } else {
                                if (string_equals2(ch, "Ç")){
                                    string_append(modified, "C");
                                } else {
                                    if (string_equals2(ch, "Ö")){
                                        string_append(modified, "O");
                                    } else {
                                        if (string_equals2(ch, "Ğ")){
                                            string_append(modified, "G");
                                        } else {
                                            if (string_equals2(ch, "Ü")){
                                                string_append(modified, "U");
                                            } else {
                                                if (string_equals2(ch, "Ş")){
                                                    string_append(modified, "S");
                                                } else {
                                                    if (string_equals2(ch, "İ")){
                                                        string_append(modified, "I");
                                                    } else {
                                                        string_append(modified, ch->s);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    free_array_list(chars, (void (*)(void *)) free_string_ptr);
    char* result = NULL;
    result = str_copy(result, modified->s);
    free_string_ptr(modified);
    return result;
}

/**
 * Another asciify method which takes a Sentence as an input. It loops i times where i ranges form 0 to number of
 * words in the given sentence. First it gets each word and calls asciify with current word and creates Word
 * with returned String. At the and, adds each newly created ascified words to the result Sentence.
 *
 * @param sentence Sentence type input.
 * @return Sentence output which is asciified.
 */
Sentence_ptr asciify_sentence(Sentence_ptr sentence) {
    char* word;
    Sentence_ptr result = create_sentence();
    for (int i = 0; i < sentence->words->size; i++) {
        word = sentence_get_word(sentence, i);
        char* newWord = asciify_word(word);
        sentence_add_word(result, newWord);
    }
    return result;
}
