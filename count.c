#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{
    struct TrieNode *children[26];
    int count;
};

// Trie structure
struct Trie
{
    struct TrieNode *root;
};

// Initializes a trie node
struct TrieNode *createTrieNode()
{
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < 26; i++)
    {
        newNode->children[i] = NULL;
    }
    newNode->count = 0;
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct TrieNode *current = pTrie->root;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
        {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }

    current->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    struct TrieNode *current = pTrie->root;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
        {
            return 0;
        }
        current = current->children[index];
    }

    return current->count;
}

// Deallocates the trie structure recursively
void deallocateTrieNode(struct TrieNode *node)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < 26; i++)
    {
        deallocateTrieNode(node->children[i]);
    }

    free(node);
}

// Deallocates the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    deallocateTrieNode(pTrie->root);
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->root = createTrieNode();
    return pTrie;
}

// This function will return the number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open the dictionary file.\n");
        exit(1);
    }

    int numWords;
    fscanf(file, "%d", &numWords);

    for (int i = 0; i < numWords; ++i)
    {
        pInWords[i] = (char *)malloc(256 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // Words to check occurrences
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");

    // Free memory allocated for inWords
    for (int i = 0; i < numWords; ++i)
    {
        free(inWords[i]);
    }

    return 0;
}
