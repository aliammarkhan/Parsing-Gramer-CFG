# Parsing-Grammer-CFG
A program to implement the CFG and parse the sentence provided by user

## Grammar

![Grammar](https://user-images.githubusercontent.com/50051546/91566349-f54dc880-e95c-11ea-98fc-dc2d1c8dd527.png)

## List of Corpus:

Nouns: http://www.desiquintans.com/downloads/nounlist/nounlist.txt

Verbs: https://www.talkenglish.com/vocabulary/top-1000-verbs.aspx

Prepositions: https://www.thefreedictionary.com/List-of-prepositions.htm

Pronouns: http://www.esldesk.com/vocabulary/pronouns

Adjectives: https://www.paperrater.com/page/lists-of-adjectives

Determiners: https://www.ef.com/wwen/english-resources/english-grammar/determiners/

Conjunctions: http://www.marshall.k12.il.us/data/webcontent/245/file/realname/files/List-ofConjunctions.pdf

## Sample Input / Output:

Valid Input:

I prefer a morning flight

Output:

S

NP VP

PRO VP

I VP

I VERB NP

I prefer NP


I prefer Det Nom

I prefer a Noun Nom

I prefer a morning Nom

I prefer a morning flight

In-Valid Input:

Student Cricket Play

Output:

Incorrect Structure 

## Sample Screenshot of output

![Grammar](https://user-images.githubusercontent.com/50051546/91566790-9ccafb00-e95d-11ea-9440-ac9e4b3c2cb5.png)
