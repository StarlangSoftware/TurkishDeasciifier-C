//
// Created by Olcay Taner YILDIZ on 20.11.2023.
//

#include <FsmMorphologicalAnalyzer.h>
#include <string.h>
#include <stdlib.h>
#include "../src/SimpleDeasciifier.h"

int main(){
    Fsm_morphological_analyzer_ptr fsm = create_fsm_morphological_analyzer3();
    Sentence_ptr s1, s2;
    char* tmp;
    s1 = create_sentence3("hakkinda");
    s2 = deasciify_sentence(fsm, s1);
    tmp = sentence_to_string(s2);
    if (strcmp(tmp, "hakkında") != 0){
        printf("Error: %s\n", tmp);
    }
    free_sentence(s1);
    free_sentence(s2);
    free(tmp);
    s1 = create_sentence3("kucuk");
    s2 = deasciify_sentence(fsm, s1);
    tmp = sentence_to_string(s2);
    if (strcmp(tmp, "küçük") != 0){
        printf("Error: %s\n", tmp);
    }
    free_sentence(s1);
    free_sentence(s2);
    free(tmp);
    s1 = create_sentence3("karsilikli");
    s2 = deasciify_sentence(fsm, s1);
    tmp = sentence_to_string(s2);
    if (strcmp(tmp, "karşılıklı") != 0){
        printf("Error: %s\n", tmp);
    }
    free_sentence(s1);
    free_sentence(s2);
    free(tmp);
    free_fsm_morphological_analyzer(fsm);
}