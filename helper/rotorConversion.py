# Nicholas Norman
# Dec 2025

# Take in a string of ABCDEFGHIJKLMNOPQRSTUVWXYZ
# and map to a second string (ex.) EKMFLGDQVZNTOWYHXUSPAIBRCJ
# print out the values as an int[][]; as well as a constant turnover (ring switch)

# https://www.cryptomuseum.com/crypto/enigma/wiring.htm

base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
versions = [
    # number, mapping, model name
    ["I",	"EKMFLGDQVZNTOWYHXUSPAIBRCJ", "Enigma I"],
    ["II",	"AJDKSIRUXBLHWTMCQGZNPYFVOE", "Enigma I"],
    ["III",	"BDFHJLCPRTXVZNYEIWGAKMUSQO", "Enigma I"],
    ["IV",	"ESOVPZJAYQUIRHXLNFTGKDCMWB", "Enigma I"],
    ["V",	"VZBRGITYUPSDNHLXAWMJQOFECK", "Enigma I"],
    ["UKW_B", "YRUHQSLDPXNGOKMIEBFZCWVJAT", "Enigma I"]
]

def createMapping(base, version):
    
    mapping = "const int "
    mapping += version[2].replace(' ', '_')
    mapping += "_" + version[0]
    mapping += "[26][2] = {"
    
    for i in range(0,len(base)):
        
        # get current letter
        currentLetter = base[i]
        
        # get index of letter in version
        nextIndex = version[1].index(currentLetter)
        
        mapping += "{" + f"{i},{nextIndex}" + "},"
        
    mapping += "};"
    
    return mapping

for i in range(0, len(versions)):
    print(createMapping(base, versions[i]))