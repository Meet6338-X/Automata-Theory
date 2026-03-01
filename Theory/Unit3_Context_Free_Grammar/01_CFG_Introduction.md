# Unit 3: Context Free Grammar

## 🎯 Learning Objectives
- Chomsky Hierarchy
- CFG definition and derivations
- Parse trees and ambiguity
- CNF and GNF conversions

---

## 1.1 Chomsky Hierarchy

| Type | Grammar | Machine | Language |
|------|---------|---------|----------|
| 3 | Regular | FA | Regular |
| 2 | Context-Free | PDA | CFL |
| 1 | Context-Sensitive | LBA | CSL |
| 0 | Unrestricted | TM | REL |

---

## 1.2 CFG Definition

**G = (V, T, P, S)**
- V: Non-terminals
- T: Terminals
- P: Productions A → α
- S: Start symbol

**Example:**
S → aSb | ε generates {aⁿbⁿ | n ≥ 0}

---

## 1.3 Derivations

**Leftmost:** Expand leftmost non-terminal first
**Rightmost:** Expand rightmost non-terminal first

---

## 1.4 Ambiguity

A grammar is ambiguous if a string has multiple parse trees.

**Fix:** Add precedence/associativity rules

---

## 1.5 CNF (Chomsky Normal Form)

Productions: A → BC or A → a

**Conversion Steps:**
1. New start symbol
2. Remove ε-productions
3. Remove unit productions
4. Convert long productions

---

## 💪 Exercises

1. Write CFG for palindromes
2. Check if grammar is ambiguous
3. Convert to CNF
4. Draw parse trees
5. Generate derivation sequences

---

*"CFGs describe nested structures!"*
