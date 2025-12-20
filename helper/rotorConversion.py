# Nicholas Norman
# Dec 2025

# Take in a string of ABCDEFGHIJKLMNOPQRSTUVWXYZ
# and map to a second string (ex.) EKMFLGDQVZNTOWYHXUSPAIBRCJ
# print out the values as an int[][]; as well as a constant turnover (ring switch)

# https://www.cryptomuseum.com/crypto/enigma/wiring.htm

base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
versions = [
    # number, mapping, model name
    # ["I",	"EKMFLGDQVZNTOWYHXUSPAIBRCJ", "Enigma I"],
    # ["II",	"AJDKSIRUXBLHWTMCQGZNPYFVOE", "Enigma I"],
    # ["III",	"BDFHJLCPRTXVZNYEIWGAKMUSQO", "Enigma I"],
    # ["IV",	"ESOVPZJAYQUIRHXLNFTGKDCMWB", "Enigma I"],
    # ["V",	"VZBRGITYUPSDNHLXAWMJQOFECK", "Enigma I"],
    # ["UKW_B", "YRUHQSLDPXNGOKMIEBFZCWVJAT", "Enigma I"]
    
    ["I",	"EKMFLGDQVZNTOWYHXUSPAIBRCJ", "Enigma M3"],
    ["II",	"AJDKSIRUXBLHWTMCQGZNPYFVOE", "Enigma M3"],
    ["III",	"BDFHJLCPRTXVZNYEIWGAKMUSQO", "Enigma M3"],
    ["IV",	"ESOVPZJAYQUIRHXLNFTGKDCMWB", "Enigma M3"],
    ["V",	"VZBRGITYUPSDNHLXAWMJQOFECK", "Enigma M3"],
    ["UKW_B",	"YRUHQSLDPXNGOKMIEBFZCWVJAT", "Enigma M3"],
]

def createMapping(base, version):
    
    mapping = "std::array<std::array<int,2>,26> "
    mapping += version[2].replace(' ', '_')
    mapping += "_" + version[0]
    mapping += " = {{ "
    
    for i in range(0,len(base)):
        
        # get current letter
        currentLetter = version[1][i]
        
        # get index of letter in version
        nextIndex = base.index(currentLetter)
        
        mapping += "{" + f"{i},{nextIndex}" + "},"
        
    mapping += " }};"
    
    return mapping

for i in range(0, len(versions)):
    print(createMapping(base, versions[i]))