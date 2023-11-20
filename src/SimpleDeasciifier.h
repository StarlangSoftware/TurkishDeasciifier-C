//
// Created by Olcay Taner YILDIZ on 19.11.2023.
//

#ifndef DEASCIIFIER_SIMPLEDEASCIIFIER_H
#define DEASCIIFIER_SIMPLEDEASCIIFIER_H

#include <ArrayList.h>
#include <FsmMorphologicalAnalyzer.h>

void generate_candidate_list(Array_list_ptr candidates, const char* word, int index);

Array_list_ptr candidate_list(Fsm_morphological_analyzer_ptr fsm, const char* word);

Sentence_ptr deasciify_sentence(Fsm_morphological_analyzer_ptr fsm, Sentence_ptr sentence);

#endif //DEASCIIFIER_SIMPLEDEASCIIFIER_H
