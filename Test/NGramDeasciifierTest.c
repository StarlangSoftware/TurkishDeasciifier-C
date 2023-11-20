//
// Created by Olcay Taner YILDIZ on 20.11.2023.
//

#include <FsmMorphologicalAnalyzer.h>
#include <NGram.h>
#include <NoSmoothing.h>
#include <string.h>
#include <LaplaceSmoothing.h>
#include "../src/NGramDeasciifier.h"

void test_sentence(N_gram_deasciifier_ptr deasciifier, char* sentence1, char* sentence2){
    Sentence_ptr s1 = create_sentence3(sentence1);
    Sentence_ptr s2 = n_gram_deasciify_sentence(deasciifier, s1);
    if (strcmp(sentence_to_string(s2), sentence2) != 0){
        printf("Error is sentence %s", sentence_to_string(s2));
    }
    free_sentence(s1);
    free_sentence(s2);
}

int main(){
    Fsm_morphological_analyzer_ptr fsm = create_fsm_morphological_analyzer3();
    N_gram_ptr n_gram = create_string_n_gram3("ngram.txt");
    set_probabilities_simple(n_gram, NULL, set_probabilities_with_level_no_smoothing);
    N_gram_deasciifier_ptr deasciifier = create_n_gram_deasciifier(fsm, n_gram, false);
    test_sentence(deasciifier, "noter hakkinda", "noter hakkında");
    test_sentence(deasciifier, "sandik medrese", "sandık medrese");
    test_sentence(deasciifier, "kuran'ı karsilikli", "kuran'ı karşılıklı");
    double delta[] = {1.0};
    set_probabilities_simple(n_gram, delta, set_probabilities_with_level_laplace_smoothing);
    test_sentence(deasciifier, "dün aksam yenı aldıgımız çam ağacını susledık", "dün akşam yeni aldığımız çam ağacını süsledik");
    test_sentence(deasciifier, "unlu sanatçı tartismali konu hakkinda demec vermekten kacindi", "ünlü sanatçı tartışmalı konu hakkında demeç vermekten kaçındı");
    test_sentence(deasciifier, "koylu de durumdan oldukca şikayetciydi", "köylü de durumdan oldukça şikayetçiydi");
    free_n_gram_deasciifier(deasciifier);
}