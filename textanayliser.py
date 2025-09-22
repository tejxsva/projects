import string

def analyze_text(text):
    # Remove punctuation
    text_no_punct = text.translate(str.maketrans('', '', string.punctuation))
    # Convert to lowercase
    text_lower = text_no_punct.lower()
    # Split into words
    words = text_lower.split()
    # Count words
    word_count = len(words)
    # Count sentences (simple split by . ! ?)
    sentence_count = text.count('.') + text.count('!') + text.count('?')
    # Character count (excluding spaces)
    char_count = len(text.replace(' ', ''))
    # Word frequency
    word_freq = {}
    for word in words:
        word_freq[word] = word_freq.get(word, 0) + 1

    # Output results
    print(f"\nTotal words: {word_count}")
    print(f"Total sentences: {sentence_count}")
    print(f"Total characters (excluding spaces): {char_count}")
    print("Word frequencies:")
    for word, freq in word_freq.items():
        print(f"{word}: {freq}")

if __name__ == "__main__":
    user_text = input("Enter text to analyze:\n")
    analyze_text(user_text)
