//
// Created by Olcay Taner YILDIZ on 19.11.2023.
//

#ifndef DEASCIIFIER_NGRAMDEASCIIFIER_H
#define DEASCIIFIER_NGRAMDEASCIIFIER_H
#include <NGram.h>
#include <FsmMorphologicalAnalyzer.h>

struct n_gram_deasciifier{
    Fsm_morphological_analyzer_ptr fsm;
    N_gram_ptr n_gram;
    bool root_n_gram;
    double threshold;
    Hash_map_ptr asciified_same;
};

typedef struct n_gram_deasciifier N_gram_deasciifier;

typedef N_gram_deasciifier *N_gram_deasciifier_ptr;

N_gram_deasciifier_ptr create_n_gram_deasciifier(Fsm_morphological_analyzer_ptr fsm,
                                                 N_gram_ptr n_gram,
                                                 bool root_n_gram);

void free_n_gram_deasciifier(N_gram_deasciifier_ptr deasciifier);

Sentence_ptr n_gram_deasciify_sentence(N_gram_deasciifier_ptr deasciifier, Sentence_ptr sentence);

Word_ptr check_analysis_and_set_root(N_gram_deasciifier_ptr deasciifier,
                                     Sentence_ptr sentence,
                                     int index);

#endif //DEASCIIFIER_NGRAMDEASCIIFIER_H
