#LastName: Andrews
#FirstName: Taylor
#Email: taylor.andrews-1@colorado.edu
#Comments:

from __future__ import print_function
import sys

# We will use a class called my trie node
class MyTrieNode:
    # Initialize some fields 
  
    def __init__(self, isRootNode):
        #The initialization below is just a suggestion.
        #Change it as you will.
        # But do not change the signature of the constructor.
        self.isRoot = isRootNode
        self.isWordEnd = False # is this node a word ending node
        self.count = 0 # frequency count
        self.next = {} # Dictionary mappng each character from a-z to the child node


    def addWord(self,w):
        assert(len(w) > 0)
        
        self.add(w, self)
        
    #Helper function to recursively add to the trie
    def add(self, word, node):
        if not word:
                return
            
        char = word[:1]
        
        if char not in node.next:
            child = MyTrieNode(False) #Create the next node in the trie
            node.next[char] = child #Link the nodes using the dict

            if len(word) == 1:
                child.isWordEnd = True #Since there is only one letter left this must be the end of a word
                child.count += 1 #Increment the count of child

            self.add(word[1:], child)
        else:
            if len(word) == 1:
                node.next[char].isWordEnd = True #Since there is only one letter left this must be the end of a word
                node.next[char].count += 1 #Increment the count of the existant child

            self.add(word[1:], node.next[char]) #Recursively add
        
        return

    def lookupWord(self, w):
        # Return frequency of occurrence of the word w in the trie
        # returns a number for the frequency and 0 if the word w does not occur.
        if not w:
            return 0

        node = self.findNode(w, self) #Search for the node in the trie using findNode
		
        try:
            return node.count #If the value returned by findNode is -1, this will pass control to the except
        except:
            return 0 #Return 0 for count if the word is not in the trie

    #findNode will find the last node associated with any word in the Trie
    #  If the word does not exist in the Trie, findNode returns -1
    def findNode(self, word, node):
        char = word[:1]
        
        if char not in node.next:
            return -1 #The word doesn't exist in the trie
        elif len(word) == 1:
            return node.next[char] #Return the last node in the word
        else:
            return self.findNode(word[1:], node.next[char]) #Recursively search

    def autoComplete(self,w):
        #Returns possible list of autocompletions of the word w
        #Returns a list of pairs (s,j) denoting that
        #         word s occurs with frequency j
        if not w:
            return [] #Return the empty set in the case of a blank word
            
        node = self.findNode(w, self)    
        lst = []

        try:
            if node.isWordEnd: #If the value returned by findNode is -1, this will pass control to the except
                lst.append( (w, node.count) ) #If the word is already in the trie, add it as a suggestion
        except:
            return lst #Return an empty list if the word is not in the trie
            
        return self.auto(w, node, lst) 

    #Recursive helper function for autocomplete
    def auto(self, suggestion, node, lst):
        for key, value in node.next.items(): 
            if node.next[key].isWordEnd: 
                lst.append( (suggestion+key,node.next[key].count) ) #Append to the list of word suggestions
            self.auto(suggestion+key, node.next[key], lst) #Recursively autocomplete
            
        return lst

if (__name__ == '__main__'):
    t= MyTrieNode(True)
    lst1=['test','testament','testing','ping','pin','pink','pine','pint','testing','pinetree']

    for w in lst1:
        t.addWord(w)

    j = t.lookupWord('testy') # should return 0
    j2 = t.lookupWord('telltale') # should return 0
    j3 = t.lookupWord ('testing') # should return 2

    lst3 = t.autoComplete('pi')
    print('Completions for \"pi\" are : ')
    print(lst3)
    
    lst4 = t.autoComplete('tes')
    print('Completions for \"tes\" are : ')
    print(lst4)
