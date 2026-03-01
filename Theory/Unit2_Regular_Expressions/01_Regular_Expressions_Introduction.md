# Unit 2: Regular Expressions and Regular Languages

## 🎯 Learning Objectives
- Master regular expression syntax and semantics
- Convert between RE and FA
- Understand Kleene's Theorem
- Apply Arden's Theorem
- Know closure properties

---

## 1.1 What are Regular Expressions?

### 💡 Real-World Analogy
Regular expressions are like **search patterns**:
- Ctrl+F in documents
- File search patterns (*.txt)
- Email validation rules
- Phone number formats

### 📌 Formal Definition

A **Regular Expression** over alphabet Σ is defined recursively:

1. **∅** is a RE (empty language)
2. **ε** is a RE (language containing only empty string)
3. **a** is a RE for each a ∈ Σ
4. If r and s are REs, then:
   - **(r + s)** is a RE (union)
   - **(r · s)** is a RE (concatenation)
   - **(r*)** is a RE (Kleene star)

---

## 1.2 Regular Expression Operators

| Operator | Symbol | Meaning | Example |
|----------|--------|---------|---------|
| Union | + or \| | OR | a+b = {a} ∪ {b} |
| Concatenation | · or juxtaposition | AND then | ab = {ab} |
| Kleene Star | * | Zero or more | a* = {ε, a, aa, aaa, ...} |
| Positive Closure | + | One or more | a+ = {a, aa, aaa, ...} |
| Optional | ? | Zero or one | a? = {ε, a} |

---

## 1.3 Examples of Regular Expressions

### Basic Patterns

| Pattern | Language | Examples |
|---------|----------|----------|
| a* | All strings of a's | ε, a, aa, aaa... |
| a+b* | a followed by b's | a, ab, abb, abbb... |
| (a+b)* | Any mix of a and b | ε, a, b, aa, ab, ba, bb... |
| a*b* | Some a's then some b's | ε, a, b, aa, ab, bb, aab... |
| (aa)* | Even number of a's | ε, aa, aaaa, aaaaaa... |

### Practical Examples

| Pattern | Description |
|---------|-------------|
| (0+1)*00 | Binary strings ending in 00 |
| 1(0+1)*0 | Strings starting with 1, ending with 0 |
| (a+b)*ab(a+b)* | Strings containing 'ab' as substring |
| b*(ab*ab*)* | Strings with even number of a's |

---

## 1.4 Converting RE to NFA (Thompson's Construction)

### Rules

**1. Base Cases:**
- ε: Start → Final
- a: Start --a--> Final
- ∅: No path

**2. Inductive Cases:**
- Union (r+s): Parallel connection
- Concatenation (rs): Serial connection
- Star (r*): Loop back connection

### Example: Convert (a+b)*ab to NFA

Step 1: Build NFA for a+b
Step 2: Apply star
Step 3: Concatenate with ab

---

## 1.5 Kleene's Theorem

### Statement
**Three statements are equivalent:**
1. L is a Regular Language
2. L is accepted by some DFA
3. L is described by some Regular Expression

### Proof Sketch
- RE → ε-NFA (Thompson's construction)
- ε-NFA → NFA (ε-removal)
- NFA → DFA (Subset construction)
- DFA → RE (State elimination / Arden's theorem)

---

## 1.6 Arden's Theorem

### Statement
If P and Q are regular expressions over Σ, and P does not contain ε, then:

**R = Q + RP has unique solution: R = QP***

### Application: DFA to RE

**Algorithm:**
1. Create equations for each state
2. Solve using Arden's theorem
3. Equation for final state gives RE

### Example

Equations:
- q₀ = ε + q₁a + q₀b
- q₁ = q₀a
- q₂ = q₁b + q₂a + q₂b

Solving step-by-step...

---

## 1.7 Closure Properties

Regular Languages are closed under:

| Operation | Result |
|-----------|--------|
| Union | L₁ ∪ L₂ is regular |
| Intersection | L₁ ∩ L₂ is regular |
| Complement | L̄ is regular |
| Concatenation | L₁ · L₂ is regular |
| Kleene Star | L* is regular |
| Difference | L₁ - L₂ is regular |
| Reversal | Lᴿ is regular |
| Homomorphism | h(L) is regular |

**Proof Techniques:**
- Union: RE (r+s) or parallel FA
- Complement: Swap final/non-final in DFA
- Intersection: Product construction

---

## 💪 Practice Exercises

### Exercise 1: RE Construction
Write RE for:
a) Strings over {0,1} with exactly two 0s
b) Strings where every 0 is followed by at least one 1
c) Strings with even length

### Exercise 2: Language Analysis
Describe the language of:
a) (a+b)*aa(a+b)*
b) b*(ab*ab*)*
c) (0+1)*1(0+1)(0+1)

### Exercise 3: Conversion
Convert RE to NFA:
a) (ab+a)*
b) a*b*c*

### Exercise 4: Arden's Theorem
Solve: X = aX + b

### Exercise 5: Closure Properties
Prove regular languages are closed under:
a) Intersection
b) Reversal

---

## 🔑 Key Takeaways

1. **RE = Regular Language** (Kleene's Theorem)
2. **Three operators:** Union, Concatenation, Star
3. **Conversion algorithms:** Thompson's (RE→FA), Arden's (FA→RE)
4. **Closure properties:** Regular languages closed under many operations
5. **Precedence:** Star > Concatenation > Union

---

*"Regular Expressions are the DNA of pattern matching!" - Your Automata Teacher*
