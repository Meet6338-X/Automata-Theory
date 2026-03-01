# DFA: Deterministic Finite Automata

## 🎯 Learning Objectives
- Understand what DFA is and how it works
- Design DFAs for given languages
- Formal definition and components of DFA
- Trace DFA execution on input strings

---

## 2.1 What is a DFA?

### 💡 Real-World Analogy
Think of a **vending machine**:
- It has different states (idle, selecting, dispensing)
- You put in coins (input symbols)
- Based on current state and input, it moves to next state
- Some states give you your snack (accepting states)!

A DFA works exactly the same way!

---

### 📌 Formal Definition

A **Deterministic Finite Automaton (DFA)** is a 5-tuple:

**M = (Q, Σ, δ, q₀, F)**

Where:
| Component | Symbol | Meaning |
|-----------|--------|---------|
| States | Q | Finite set of states |
| Alphabet | Σ | Finite set of input symbols |
| Transition Function | δ | δ: Q × Σ → Q (state changes) |
| Start State | q₀ | Initial state (q₀ ∈ Q) |
| Final States | F | Set of accepting states (F ⊆ Q) |

---

## 2.2 How DFA Works

### The DFA Algorithm
```
1. Start at initial state q₀
2. For each input symbol:
   a. Look at current state
   b. Look at input symbol
   c. Use δ to find next state
   d. Move to next state
3. After processing all input:
   - If in final state → ACCEPT ✓
   - Otherwise → REJECT ✗
```

---

## 2.3 DFA Example 1: Strings ending with '01'

### Problem
Design a DFA that accepts all binary strings ending with "01"

### Solution

**States needed:**
- q₀: Start state (haven't seen pattern)
- q₁: Just saw '0'
- q₂: Saw '01' (FINAL STATE)

**Transition Table:**

| State | 0 | 1 |
|-------|---|---|
| →q₀   | q₁| q₀|
| q₁    | q₁| q₂|
| *q₂   | q₁| q₀|

**State Diagram:**
```
       0          1
   ┌────────►q1────────┐
   │         │         │
   │    1    │    0    ▼
──►(q0)      │        (q2)
   start     │        final
    │        ▼          │
    └───────────────────┘
              1
```

**Execution Trace for "1001":**
| Step | Input | Current | Next | Calculation |
|------|-------|---------|------|-------------|
| 1    | 1     | q₀      | q₀   | δ(q₀,1)=q₀ |
| 2    | 0     | q₀      | q₁   | δ(q₀,0)=q₁ |
| 3    | 0     | q₁      | q₁   | δ(q₁,0)=q₁ |
| 4    | 1     | q₁      | q₂   | δ(q₁,1)=q₂ |

Final state: q₂ ∈ F → **ACCEPTED** ✓

**Execution Trace for "1010":**
| Step | Input | Current | Next |
|------|-------|---------|------|
| 1    | 1     | q₀      | q₀   |
| 2    | 0     | q₀      | q₁   |
| 3    | 1     | q₁      | q₂   |
| 4    | 0     | q₂      | q₁   |

Final state: q₁ ∉ F → **REJECTED** ✗

---

## 2.4 DFA Example 2: Even number of 0s

### Problem
Design DFA for binary strings with even number of 0s

### Solution

**States:**
- q₀: Even 0s (START and FINAL)
- q₁: Odd 0s

**Transition Table:**

| State | 0 | 1 |
|-------|---|---|
| →*q₀  | q₁| q₀|
| q₁    | q₀| q₁|

**Why this works:**
- Each '0' flips between even and odd
- '1' doesn't affect the count

**State Diagram:**
```
        0                    
   ┌──────────►            
   │          │            
   │    0     │            
──►((q0))◄────┘            
   final    │              
    │  1    │              
    │       │ 1            
    └──►(q1)◄──┘           
```

---

## 2.5 DFA Example 3: Strings containing '001' as substring

### Problem
Accept all strings that have "001" somewhere

### Solution

**States:**
- q₀: Start, no relevant prefix
- q₁: Saw '0'
- q₂: Saw '00'
- q₃: Saw '001' (FINAL - pattern found!)

**Transition Table:**

| State | 0 | 1 |
|-------|---|---|
| →q₀   | q₁| q₀|
| q₁    | q₂| q₀|
| q₂    | q₂| q₃|
| *q₃   | q₃| q₃|

**Key Insight:** Once in q₃, stay there (trap state with acceptance)

---

## 2.6 Design Strategy for DFAs

### Step-by-Step Approach:

1. **Understand the Language**
   - What must the string contain?
   - What pattern must it follow?
   - What are the constraints?

2. **Identify What to Remember**
   - What information from the past affects future decisions?
   - How much of the input history matters?

3. **Create States for Each Memory Configuration**
   - Each state represents "what I know so far"

4. **Define Transitions**
   - For each state and each input, where to go?

5. **Identify Final States**
   - Which states mean "accept"?

---

## 📝 Worked Examples

### Example 1: Design DFA for strings starting with '1'

**Solution:**
- q₀: Start
- q₁: Saw '1' first (FINAL)
- q₂: Dead state (saw '0' first)

| State | 0 | 1 |
|-------|---|---|
| →q₀   | q₂| q₁|
| *q₁   | q₁| q₁|
| q₂    | q₂| q₂|

### Example 2: Design DFA for strings with at least one 'a' and one 'b'

**Solution:**
Need to track: seen 'a'? seen 'b'?
- q₀: Nothing seen
- q₁: Saw 'a' only
- q₂: Saw 'b' only
- q₃: Saw both (FINAL)

| State | a | b |
|-------|---|---|
| →q₀   | q₁| q₂|
| q₁    | q₁| q₃|
| q₂    | q₃| q₂|
| *q₃   | q₃| q₃|

---

## 💪 Practice Exercises

### Exercise 1: Basic DFA Design
Design DFAs for:
a) Strings over {a,b} ending with 'aa'
b) Binary strings with even number of 1s
c) Strings over {0,1} that contain '111' as substring

### Exercise 2: Trace Execution
For the DFA: Q={q0,q1,q2}, Σ={0,1}, F={q2}
δ:
- δ(q0,0)=q0, δ(q0,1)=q1
- δ(q1,0)=q2, δ(q1,1)=q1
- δ(q2,0)=q2, δ(q2,1)=q1

Trace these strings:
a) 001
b) 110
c) 0101

### Exercise 3: Language Understanding
Given DFA with states {A,B,C}, start A, final {C}
δ(A,0)=B, δ(A,1)=A
δ(B,0)=C, δ(B,1)=B
δ(C,0)=C, δ(C,1)=B

Describe the language accepted in English.

### Exercise 4: Advanced Design
Design DFA for:
a) Binary numbers divisible by 3
b) Strings where every 'a' is followed by 'bb'
c) Strings with exactly two 'a's

### Exercise 5: Proof
Prove that if a DFA has n states, it accepts some string of length < n if it accepts any string at all.

---

## 🔑 Key Takeaways

1. **DFA = 5-tuple** (Q, Σ, δ, q₀, F)
2. **Deterministic** means exactly one transition per (state, input)
3. **No ε-transitions** in DFA
4. **Every state** must have transitions for all symbols
5. **Trap state** can be used for rejection

---

## ⚠️ Common Mistakes

| Mistake | Correction |
|---------|------------|
| Missing transitions | Every state needs all symbol transitions |
| Wrong final states | Carefully check which states should be final |
| Not handling all cases | Consider edge cases like empty string |
| Confusing deterministic | Only ONE transition per (state, input) |

---

## 🎓 Next Topic
Next, we'll learn about NFA (Nondeterministic Finite Automata) which allows multiple transitions and ε-moves!
