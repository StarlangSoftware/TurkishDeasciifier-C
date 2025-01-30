//
// Created by Olcay Taner YILDIZ on 19.11.2023.
//

#include <Dictionary/Word.h>
#include <stdlib.h>
#include <Memory/Memory.h>
#include "SimpleDeasciifier.h"

/**
 * The generateCandidateList method takes an vector candidates, a String, and an integer index as inputs.
 * First, it creates a String which consists of corresponding Latin versions of special Turkish characters. If given index
 * is less than the length of given word and if the item of word's at given index is one of the chars of String, it loops
 * given candidates vector's size times and substitutes Latin characters with their corresponding Turkish versions
 * and put them to newly created char vector modified. At the end, it adds each modified item to the candidates
 * vector as a String and recursively calls generateCandidateList with next index.
 *
 * @param candidates vector type input.
 * @param word       String input.
 * @param index      Integer input.
 */
void generate_candidate_list(Array_list_ptr candidates, const char *word, int index) {
    char* s = "ıiougcsİIOUGCS";
    String_ptr modified;
    if (index < word_size(word)) {
        String_ptr ch = char_at(word, index);
        if (str_contains(s, ch->s)) {
            int size = candidates->size;
            for (int i = 0; i < size; i++) {
                String_ptr s1 = substring(array_list_get(candidates, i), 0, index);
                String_ptr s2 = substring2(array_list_get(candidates, i), index + 1);
                if (string_equals2(ch, "ı")){
                    modified = create_string4(s1->s, "i", s2->s);
                } else {
                    if (string_equals2(ch, "i")){
                        modified = create_string4(s1->s, "ı", s2->s);
                    } else {
                        if (string_equals2(ch, "o")){
                            modified = create_string4(s1->s, "ö", s2->s);
                        } else {
                            if (string_equals2(ch, "u")){
                                modified = create_string4(s1->s, "ü", s2->s);
                            } else {
                                if (string_equals2(ch, "g")){
                                    modified = create_string4(s1->s, "ğ", s2->s);
                                } else {
                                    if (string_equals2(ch, "c")){
                                        modified = create_string4(s1->s, "ç", s2->s);
                                    } else {
                                        if (string_equals2(ch, "s")){
                                            modified = create_string4(s1->s, "ş", s2->s);
                                        } else {
                                            if (string_equals2(ch, "I")){
                                                modified = create_string4(s1->s, "ı", s2->s);
                                            } else {
                                                if (string_equals2(ch, "İ")){
                                                    modified = create_string4(s1->s, "I", s2->s);
                                                } else {
                                                    if (string_equals2(ch, "O")){
                                                        modified = create_string4(s1->s, "Ö", s2->s);
                                                    } else {
                                                        if (string_equals2(ch, "U")){
                                                            modified = create_string4(s1->s, "Ü", s2->s);
                                                        } else {
                                                            if (string_equals2(ch, "G")){
                                                                modified = create_string4(s1->s, "Ğ", s2->s);
                                                            } else {
                                                                if (string_equals2(ch, "C")){
                                                                    modified = create_string4(s1->s, "Ç", s2->s);
                                                                } else {
                                                                    if (string_equals2(ch, "S")){
                                                                        modified = create_string4(s1->s, "Ş", s2->s);
                                                                    } else {
                                                                        modified = create_string2(array_list_get(candidates, i));
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
                }
                free_string_ptr(s1);
                free_string_ptr(s2);
                char* added = str_copy(added, modified->s);
                free_string_ptr(modified);
                array_list_add(candidates, added);
            }
        }
        free_string_ptr(ch);
        generate_candidate_list(candidates, word, index + 1);
    }
}

/**
 * The candidateList method takes a Word as an input and creates new candidates vector. First it
 * adds given word to this vector and calls generateCandidateList method with candidates, given word and
 * index 0. Then, loops i times where i ranges from 0 to size of candidates vector and calls morphologicalAnalysis
 * method with ith item of candidates vector. If it does not return any analysis for given item, it removes
 * the item from candidates vector.
 *
 * @param fsm Current morphological analyzer
 * @param word Word type input.
 * @return ArrayList candidates.
 */
Array_list_ptr candidate_list(Fsm_morphological_analyzer_ptr fsm, const char *word) {
    Array_list_ptr candidates = create_array_list();
    Array_list_ptr result = create_array_list();
    char* tmp = NULL;
    tmp = str_copy(tmp, word);
    array_list_add(candidates, tmp);
    generate_candidate_list(candidates, word, 0);
    for (int i = 0; i < candidates->size; i++) {
        char* candidate = array_list_get(candidates, i);
        Fsm_parse_list_ptr fsmParseList = morphological_analysis(fsm, candidate);
        if (fsmParseList->fsm_parses->size != 0) {
            tmp = str_copy(tmp, candidate);
            array_list_add(result, tmp);
        }
        free_fsm_parse_list(fsmParseList);
    }
    free_array_list(candidates, free_);
    return result;
}

/**
 * The deasciify method takes a Sentence as an input and loops i times where i ranges from 0 to number of
 * words in the given Sentence. First it gets ith word from given Sentence and calls candidateList with
 * ith word and assigns the returned vector to the newly created candidates vector. And if the size of
 * candidates vector is greater than 0, it generates a random number and gets the item of candidates vector
 * at the index of random number and assigns it as a newWord. If the size of candidates vector is 0, it then
 * directly assigns ith word as the newWord. At the end, it adds newWord to the result Sentence.
 *
 * @param fsm Current morphological analyzer object
 * @param sentence Sentence type input.
 * @return result Sentence.
 */
Sentence_ptr deasciify_sentence(Fsm_morphological_analyzer_ptr fsm, Sentence_ptr sentence) {
    char* word, *new_word = NULL;
    int random_candidate;
    Array_list_ptr candidates;
    Sentence_ptr result = create_sentence();
    for (int i = 0; i < sentence->words->size; i++) {
        word = sentence_get_word(sentence, i);
        Fsm_parse_list_ptr fsmParseList = morphological_analysis(fsm, word);
        if (fsmParseList->fsm_parses->size == 0){
            candidates = candidate_list(fsm, word);
            if (candidates->size != 0) {
                random_candidate = random() % candidates->size;
                new_word = str_copy(new_word, array_list_get(candidates, random_candidate));
            } else {
                new_word = str_copy(new_word, word);
            }
            free_array_list(candidates, free_);
        } else {
            new_word = str_copy(new_word, word);
        }
        free_fsm_parse_list(fsmParseList);
        sentence_add_word(result, new_word);
    }
    return result;
}
