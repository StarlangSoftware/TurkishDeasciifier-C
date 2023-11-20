//
// Created by Olcay Taner YILDIZ on 18.11.2023.
//

#ifndef DEASCIIFIER_SIMPLEASCIIFIER_H
#define DEASCIIFIER_SIMPLEASCIIFIER_H

#include <Dictionary/Word.h>
#include <Sentence.h>

char* asciify_word(char* word);

Sentence_ptr asciify_sentence(Sentence_ptr sentence);

#endif //DEASCIIFIER_SIMPLEASCIIFIER_H
