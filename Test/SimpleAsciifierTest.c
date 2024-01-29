//
// Created by Olcay Taner YILDIZ on 20.11.2023.
//

#include <string.h>
#include <stdlib.h>
#include <Memory/Memory.h>
#include "../src/SimpleAsciifier.h"

int main(){
    char* st = asciify_word("çöğüşıÇÖĞÜŞİ");
    if (strcmp(st, "cogusiCOGUSI") != 0){
        printf("Error in %s\n", "çöğüşıÇÖĞÜŞİ");
    }
    free_(st);
    st = asciify_word("söğüş");
    if (strcmp(st, "sogus") != 0){
        printf("Error in %s\n", "söğüş");
    }
    free_(st);
    st = asciify_word("üçkağıtçılık");
    if (strcmp(st, "uckagitcilik") != 0){
        printf("Error in %s\n", "üçkağıtçılık");
    }
    free_(st);
    st = asciify_word("akışkanlıştırıcılık");
    if (strcmp(st, "akiskanlistiricilik") != 0){
        printf("Error in %s\n", "akışkanlıştırıcılık");
    }
    free_(st);
    st = asciify_word("çıtçıtçılık");
    if (strcmp(st, "citcitcilik") != 0){
        printf("Error in %s\n", "çıtçıtçılık");
    }
    free_(st);
    st = asciify_word("düşkırıklığı");
    if (strcmp(st, "duskirikligi") != 0){
        printf("Error in %s\n", "düşkırıklığı");
    }
    free_(st);
    st = asciify_word("yüzgörümlüğü");
    if (strcmp(st, "yuzgorumlugu") != 0){
        printf("Error in %s\n", "yüzgörümlüğü");
    }
    free_(st);
    Sentence_ptr s1, s2;
    char* tmp;
    s1 = create_sentence3("çöğüş ııı ÇÖĞÜŞİ");
    s2 = asciify_sentence(s1);
    tmp = sentence_to_string(s2);
    if (strcmp(tmp, "cogus iii COGUSI") != 0){
        printf("Error in sentence cogus iii COGUSI");
    }
    free_sentence(s1);
    free_sentence(s2);
    free_(tmp);
    s1 = create_sentence3("üçkağıtçılık akışkanlıştırıcılık");
    s2 = asciify_sentence(s1);
    tmp = sentence_to_string(s2);
    if (strcmp(tmp, "uckagitcilik akiskanlistiricilik") != 0){
        printf("Error in sentence uckagitcilik akiskanlistiricilik");
    }
    free_sentence(s1);
    free_sentence(s2);
    free_(tmp);
    s1 = create_sentence3("çıtçıtçılık düşkırıklığı yüzgörümlüğü");
    s2 = asciify_sentence(s1);
    tmp = sentence_to_string(s2);
    if (strcmp(tmp, "citcitcilik duskirikligi yuzgorumlugu") != 0){
        printf("Error in sentence citcitcilik duskirikligi yuzgorumlugu");
    }
    free_sentence(s1);
    free_sentence(s2);
    free_(tmp);
}