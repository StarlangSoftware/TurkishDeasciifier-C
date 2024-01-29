//
// Created by Olcay Taner YILDIZ on 19.11.2023.
//

#include <stdlib.h>
#include <FileUtils.h>
#include "NGramDeasciifier.h"
#include "SimpleDeasciifier.h"
#include "Memory/Memory.h"

double max(double x, double y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

/**
 * A constructor of NGramDeasciifier class which takes an FsmMorphologicalAnalyzer and an NGram
 * as inputs. It first calls it super class SimpleDeasciifier with given FsmMorphologicalAnalyzer input
 * then initializes nGram variable with given NGram input.
 *
 * @param fsm   FsmMorphologicalAnalyzer type input.
 * @param nGram NGram type input.
 */
N_gram_deasciifier_ptr create_n_gram_deasciifier(Fsm_morphological_analyzer_ptr fsm,
                                                 N_gram_ptr n_gram,
                                                 bool root_n_gram) {
    N_gram_deasciifier_ptr result = malloc_(sizeof(N_gram_deasciifier), "create_n_gram_deasciifier");
    result->n_gram = n_gram;
    result->fsm = fsm;
    result->root_n_gram = root_n_gram;
    result->threshold = 0.0;
    result->asciified_same = read_hash_map("asciified-same.txt");
    return result;
}

/**
 * The deasciify method takes a Sentence as an input. First it creates a String ArrayList as candidates,
 * and a Sentence result. Then, loops i times where i ranges from 0 to words size of given sentence. It gets the
 * current word and generates a candidateList with this current word then, it loops through the candidateList. First it
 * calls morphologicalAnalysis method with current candidate and gets the first item as root word. If it is the first root,
 * it gets its N-gram probability, if there are also other roots, it gets probability of these roots and finds out the
 * best candidate, best root and the best probability. At the nd, it adds the bestCandidate to the bestCandidate ArrayList.
 *
 * @param sentence Sentence type input.
 * @return Sentence result as output.
 */
Sentence_ptr n_gram_deasciify_sentence(N_gram_deasciifier_ptr deasciifier, Sentence_ptr sentence) {
    char* word, *best_root, *previous_root = NULL, *root, *next_root;
    char* best_candidate;
    bool is_asciified_same;
    Fsm_parse_list_ptr fsm_parses;
    double previous_probability, next_probability, best_probability;
    Array_list_ptr candidates = create_array_list();
    Sentence_ptr result = create_sentence();
    root = check_analysis_and_set_root(deasciifier, sentence, 0);
    next_root = check_analysis_and_set_root(deasciifier, sentence, 1);
    for (int i = 0; i < sentence->words->size; i++) {
        free_array_list(candidates, free_);
        candidates = create_array_list();
        is_asciified_same = false;
        word = sentence_get_word(sentence, i);
        if (hash_map_contains(deasciifier->asciified_same, word)){
            char* tmp = str_copy(tmp, word);
            array_list_add(candidates, tmp);
            tmp = str_copy(tmp, hash_map_get(deasciifier->asciified_same, word));
            array_list_add(candidates, tmp);
            is_asciified_same = true;
        }
        if (root == NULL || is_asciified_same) {
            if (!is_asciified_same){
                free_array_list(candidates, free_);
                candidates = candidate_list(deasciifier->fsm, word);
            }
            best_candidate = word;
            best_root = word;
            best_probability = deasciifier->threshold;
            for (int j = 0; j < candidates->size; j++) {
                char* candidate = array_list_get(candidates, j);
                fsm_parses = morphological_analysis(deasciifier->fsm, candidate);
                if (deasciifier->root_n_gram && !is_asciified_same){
                    root = get_parse_with_longest_root_word(fsm_parses)->root->name;
                } else {
                    root = candidate;
                }
                if (previous_root != NULL) {
                    previous_probability = get_probability(deasciifier->n_gram, 2, previous_root, root);
                } else {
                    previous_probability = 0.0;
                }
                if (next_root != NULL) {
                    next_probability = get_probability(deasciifier->n_gram, 2, root, next_root);
                } else {
                    next_probability = 0.0;
                }
                if (max(previous_probability, next_probability) > best_probability || candidates->size == 1) {
                    best_candidate = candidate;
                    best_root = root;
                    best_probability = max(previous_probability, next_probability);
                }
                free_fsm_parse_list(fsm_parses);
            }
            root = best_root;
            sentence_add_word_copy(result, best_candidate);
        } else {
            sentence_add_word_copy(result, word);
        }
        previous_root = root;
        root = next_root;
        next_root = check_analysis_and_set_root(deasciifier, sentence, i + 2);
    }
    free_array_list(candidates, free_);
    return result;
}

/**
 * Checks the morphological analysis of the given word in the given index. If there is no misspelling, it returns
 * the longest root word of the possible analyses.
 * @param sentence Sentence to be analyzed.
 * @param index Index of the word
 * @return If the word is misspelled, null; otherwise the longest root word of the possible analyses.
 */
char* check_analysis_and_set_root(N_gram_deasciifier_ptr deasciifier,
                                     Sentence_ptr sentence,
                                     int index) {
    if (index < sentence->words->size){
        Fsm_parse_list_ptr fsm_parse_list = morphological_analysis(deasciifier->fsm, sentence_get_word(sentence, index));
        if (fsm_parse_list->fsm_parses->size != 0){
            if (deasciifier->root_n_gram){
                char* result = get_parse_with_longest_root_word(fsm_parse_list)->root->name;
                free_fsm_parse_list(fsm_parse_list);
                return result;
            } else {
                free_fsm_parse_list(fsm_parse_list);
                return sentence_get_word(sentence, index);
            }
        }
        free_fsm_parse_list(fsm_parse_list);
    }
    return NULL;
}

void free_n_gram_deasciifier(N_gram_deasciifier_ptr deasciifier) {
    free_fsm_morphological_analyzer(deasciifier->fsm);
    free_n_gram(deasciifier->n_gram);
    free_hash_map2(deasciifier->asciified_same, free_, free_);
    free_(deasciifier);
}
