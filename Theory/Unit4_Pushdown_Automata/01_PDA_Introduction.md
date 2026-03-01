# Unit 4: Pushdown Automata

## 🎯 Learning Objectives
- Understand PDA and its components
- Design PDAs for CFLs
- Acceptance by final state and empty stack
- Equivalence of PDA and CFG

---

## 1.1 What is a PDA?

### 💡 Analogy
A PDA is like a **vending machine with memory**:
- States control operation
- Input: coins selected
- Stack: tracks what products selected
- Can count unlimited items (unlike FA)

### 📌 Formal Definition

**PDA = (Q, Σ, Γ, δ, q₀, Z₀, F)**

| Component | Description |
|-----------|-------------|
| Q | States |
| Σ | Input alphabet |
| Γ | Stack alphabet |
| δ | Transition: Q × (Σ ∪ {ε}) × Γ → finite subsets of Q × Γ* |
| q₀ | Start state |
| Z₀ | Initial stack symbol |
| F | Final states |

---

## 1.2 How PDA Works

### Transition Types
**δ(q, a, X) = {(p, α)}**

- In state q
- Reading input a (or ε)
- With X on stack top
- Go to state p
- Replace X with α on stack

### Stack Operations
- **Push:** α = XY (push Y on top of X)
- **Pop:** α = ε (remove X)
- **Replace:** α = Y (replace X with Y)

---

## 1.3 Example: PDA for aⁿbⁿ

### Language
L = {aⁿbⁿ | n ≥ 0}

### Strategy
1. Push a's onto stack
2. Pop a's for each b
3. Accept if stack empty

### Transitions
```
δ(q₀, a, Z₀) = (q₀, aZ₀)   [Push first a]
δ(q₀, a, a) = (q₀, aa)     [Push more a's]
δ(q₀, b, a) = (q₁, ε)      [Start popping]
δ(q₁, b, a) = (q₁, ε)      [Continue popping]
δ(q₁, ε, Z₀) = (q₂, Z₀)    [Accept]
```

---

## 1.4 Acceptance Criteria

### 1. Acceptance by Final State
- Process entire input
- End in a final state
- Stack can be anything

### 2. Acceptance by Empty Stack
- Process entire input
- Stack is empty (only Z₀ or completely empty)
- Can end in any state

### Equivalence
**Theorem:** L is accepted by PDA by final state iff L is accepted by PDA by empty stack.

---

## 1.5 Deterministic vs Nondeterministic PDA

### DPDA
- At most one transition for (state, input, stack-top)
- Cannot have both ε and non-ε transitions

### NPDA
- Multiple choices allowed
- More powerful than DPDA

**Important:** DPDA ⊂ NPDA (proper subset)

---

## 1.6 Equivalence of PDA and CFG

### Theorem
A language is context-free iff some PDA accepts it.

### CFG to PDA
1. Convert CFG to Greibach Normal Form
2. For A → aB₁B₂...Bₖ: δ(q, a, A) contains (q, B₁B₂...Bₖ)

### PDA to CFG
For transitions, create productions based on stack changes.

---

## 💪 Practice Exercises

1. Design PDA for:
   - Palindromes
   - Balanced parentheses
   - {wwᴿ | w ∈ {a,b}*}

2. Show acceptance of "aabb" on aⁿbⁿ PDA

3. Convert CFG to PDA:
   S → aSb | ε

4. Prove DPDA is less powerful than NPDA

5. Design DPDA for:
   - Strings with more a's than b's

---

## 🔑 Key Takeaways

1. PDA = FA + Stack
2. Stack provides infinite memory (LIFO)
3. Two acceptance modes: final state, empty stack
4. PDA = CFG in expressive power
5. CFLs need stack to count/remember

---

*"With a stack, we can count the uncountable!" - Your Automata Teacher*
