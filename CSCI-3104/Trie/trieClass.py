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
            child = MyTrieNode(False) #create the next node in the trie
            node.next[char] = child #link the nodes using the dict

            if len(word) == 1:
                child.isWordEnd = True
                child.count += 1 #increment the count of child

            self.add(word[1:], child) #possibly needs to be node.next[char]
        else:
            if len(word) == 1:
                node.next[char].isWordEnd = True
                node.next[char].count += 1 #increment the count of the existant child

            self.add(word[1:], node.next[char]) #recursively add
        
        return

    def lookupWord(self,w):
        # Return frequency of occurrence of the word w in the trie
        # returns a number for the frequency and 0 if the word w does not occur.

        # YOUR CODE HERE
        
        return 0 # TODO: change this line, please
    

    def autoComplete(self,w):
        #Returns possible list of autocompletions of the word w
        #Returns a list of pairs (s,j) denoting that
        #         word s occurs with frequency j

        #YOUR CODE HERE
        
        return [('Walter',1),('Mitty',2),('Went',3),('To',4),('Greenland',2)] #TODO: change this line, please
    
    
            

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
 
    
    
     
