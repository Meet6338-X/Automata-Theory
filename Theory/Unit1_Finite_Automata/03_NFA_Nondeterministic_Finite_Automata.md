# NFA: Nondeterministic Finite Automata

## 🎯 Learning Objectives
- Understand NFA and how it differs from DFA
- Design NFAs for given languages
- Convert NFA to DFA using subset construction
- Work with ε-NFA (NFA with epsilon transitions)

---

## 3.1 What is NFA?

### 💡 Analogy: Multiple Paths
Imagine you're navigating a maze:
- **DFA**: At each intersection, there's exactly one path forward
- **NFA**: At some intersections, multiple paths exist - you can "try" any of them

**Key Insight:** NFA accepts if ANY path leads to acceptance!

---

### 📌 Formal Definition

**NFA = (Q, Σ, δ, q₀, F)**

Same components as DFA, BUT:
- **δ: Q × Σ → 2^Q** (returns a SET of states, not single state)

### DFA vs NFA Comparison

| Feature | DFA | NFA |
|---------|-----|-----|
| Next state | Exactly one | Zero or more |
| δ function | Q × Σ → Q | Q × Σ → 2^Q |
| Transitions | Single path | Multiple paths |
| Design ease | Harder | Easier |
| Implementation | Direct | Convert to DFA first |

---

## 3.2 NFA Example 1: Strings ending with '01' or '10'

### Problem
Accept strings ending with "01" OR "10"

### NFA Solution
```
        0                  1
    ┌───────┐          ┌───────┐
    │       ▼          │       ▼
──►(q0)───►(q1)──1──►((q3))    (final)
    │       │
    │       │ 0
    │       ▼
    │      (q2)
    │ 1    │
    └──────┘
           └────0────►((q4))    (final)
```

**Transition Table:**

| State | 0 | 1 |
|-------|---|---|
| →q₀   | {q₁}| {q₂}|
| q₁    | ∅ | {q₃}|
| q₂    | {q₄}| ∅ |
| *q₃   | {q₃}| {q₃}|
| *q₄   | {q₄}| {q₄}|

**Why NFA is easier here:**
- DFA would need states to track both possibilities simultaneously
- NFA just "guesses" which ending we're building toward

---

## 3.3 NFA to DFA Conversion (Subset Construction)

### The Algorithm
```
1. Start state of DFA = {start state of NFA}
2. For each unmarked DFA state:
   a. Mark it
   b. For each input symbol:
      i. Compute all NFA states reachable
      ii. Add as new DFA state if not exists
      iii. Add transition
3. Final states = any DFA state containing NFA final state
```

### Example: Convert NFA to DFA

**NFA:** Accept strings with '0' as second last symbol

States: q₀ (start), q₁, q₂ (final)
Transitions:
- δ(q₀,0) = {q₀,q₁}, δ(q₀,1) = {q₀}
- δ(q₁,0) = {q₂}, δ(q₁,1) = {q₂}

**Step 1:** Start state = {q₀}

**Step 2:** Compute transitions

| DFA State | 0 | 1 |
|-----------|---|---|
| →{q₀} | {q₀,q₁} | {q₀} |
| {q₀,q₁} | {q₀,q₁,q₂} | {q₀,q₂} |
| {q₀,q₁,q₂} | {q₀,q₁,q₂} | {q₀,q₂} |
| *{q₀,q₂} | {q₀,q₁} | {q₀} |

*States containing q₂ are final

---

## 3.4 ε-NFA (NFA with Epsilon Transitions)

### What is ε?
ε (epsilon) = empty string, "no input"

### Why ε-transitions?
- Allow state changes without consuming input
- Make design even more flexible
- Useful for combining automata

### ε-NFA Example: Strings with optional prefix

Accept: "abc" where 'a' is optional (so "abc" or "bc")

```
            ε          a         b         c
    ┌──────────────────────────────────────────►
    │      │        │         │         │
    ▼      ▼        ▼         ▼         ▼
──►(q0)──►(q1)──a──►(q2)──b──►(q3)──c──►((q4))
              ε────►
```

**ε-closure:** Set of states reachable using only ε-transitions

---

## 📝 Worked Examples

### Example 1: Design NFA for strings containing 'aa' or 'bb'

**Solution:**
```
         a                a
    ┌────────►(q1)────────►((q3))
    │                       final
──►(q0)
    │         b                b
    └────────►(q2)────────►((q4))
                             final
```

Two parallel paths - NFA accepts if either succeeds!

### Example 2: Convert NFA to DFA

**NFA:**
- Q = {p, q}, Σ = {0, 1}
- δ(p,0) = {p,q}, δ(p,1) = {q}
- δ(q,0) = ∅, δ(q,1) = {p}
- Start: p, Final: {q}

**DFA Construction:**

| DFA State | 0 | 1 | Final? |
|-----------|---|---|--------|
| →{p} | {p,q} | {q} | No |
| *{q} | ∅ | {p} | Yes |
| *{p,q} | {p,q} | {p,q} | Yes |
| ∅ | ∅ | ∅ | No |

---

## 💪 Practice Exercises

### Exercise 1: NFA Design
Design NFAs for:
a) Strings ending with '00' or '11'
b) Strings with 'aba' as substring
c) Strings where 3rd symbol from end is '1'

### Exercise 2: NFA to DFA
Convert to DFA:
- Q = {A, B, C}, Σ = {0, 1}
- δ(A,0)={A,B}, δ(A,1)={A}
- δ(B,0)={C}, δ(B,1)=∅
- δ(C,0)={C}, δ(C,1)={C}
- Start: A, Final: {C}

### Exercise 3: ε-NFA
Design ε-NFA for:
a) Strings matching: a*b*c*
b) Optional sign (+/-) followed by digits

### Exercise 4: Subset Construction
Convert this ε-NFA to DFA:
- States: {q0, q1, q2}
- q0 --ε--> q1, q1 --a--> q2
- q0 --b--> q2
- Start: q0, Final: {q2}

### Exercise 5: Proof
Prove that every NFA can be converted to an equivalent DFA.

---

## 🔑 Key Takeaways

1. **NFA allows nondeterminism:** Multiple transitions for same (state, input)
2. **ε-transitions:** Change state without reading input
3. **NFA ≅ DFA:** They recognize the same class of languages (Regular)
4. **Subset construction:** Algorithm to convert NFA → DFA
5. **NFA is easier** to design, **DFA is easier** to implement

---

## ⚠️ Common Mistakes

| Mistake | Why It's Wrong |
|---------|---------------|
| Forgetting powerset | DFA states are SETS of NFA states |
| Missing ε-closure | Must include all ε-reachable states |
| Wrong final states | Any set containing NFA final state is final |

---

## 🎓 Important Theorem

**Theorem:** For every NFA N, there exists a DFA D such that L(N) = L(D)

**Proof Sketch:** Use subset construction - DFA states = subsets of NFA states

---

*"If you can dream it in NFA, a DFA can do it too!" - Your Automata Teacher*
