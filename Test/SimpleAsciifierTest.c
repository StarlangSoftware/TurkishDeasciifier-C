//
// Created by Olcay Taner YILDIZ on 20.11.2023.
//

#include <string.h>
#include <stdlib.h>
#include "../src/SimpleAsciifier.h"

int main(){
    if (strcmp(asciify_word("çöğüşıÇÖĞÜŞİ"), "cogusiCOGUSI") != 0){
        printf("Error in %s\n", "çöğüşıÇÖĞÜŞİ");
    }
    if (strcmp(asciify_word("söğüş"), "sogus") != 0){
        printf("Error in %s\n", "söğüş");
    }
    if (strcmp(asciify_word("üçkağıtçılık"), "uckagitcilik") != 0){
        printf("Error in %s\n", "üçkağıtçılık");
    }
    if (strcmp(asciify_word("akışkanlıştırıcılık"), "akiskanlistiricilik") != 0){
        printf("Error in %s\n", "akışkanlıştırıcılık");
    }
    if (strcmp(asciify_word("çıtçıtçılık"), "citcitcilik") != 0){
        printf("Error in %s\n", "çıtçıtçılık");
    }
    if (strcmp(asciify_word("düşkırıklığı"), "duskirikligi") != 0){
        printf("Error in %s\n", "düşkırıklığı");
    }
    if (strcmp(asciify_word("yüzgörümlüğü"), "yuzgorumlugu") != 0){
        printf("Error in %s\n", "yüzgörümlüğü");
    }
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
    free(tmp);
    s1 = create_sentence3("üçkağıtçılık akışkanlıştırıcılık");
    s2 = asciify_sentence(s1);
    tmp = sentence_to_string(s2);
    if (strcmp(tmp, "uckagitcilik akiskanlistiricilik") != 0){
        printf("Error in sentence uckagitcilik akiskanlistiricilik");
    }
    free_sentence(s1);
    free_sentence(s2);
    free(tmp);
    s1 = create_sentence3("çıtçıtçılık düşkırıklığı yüzgörümlüğü");
    s2 = asciify_sentence(s1);
    tmp = sentence_to_string(s2);
    if (strcmp(tmp, "citcitcilik duskirikligi yuzgorumlugu") != 0){
        printf("Error in sentence citcitcilik duskirikligi yuzgorumlugu");
    }
    free_sentence(s1);
    free_sentence(s2);
    free(tmp);
}