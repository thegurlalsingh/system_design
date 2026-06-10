# System Design Interview Questions & Answers

## Table of Contents
1. [Scalability & Architecture](#scalability--architecture)
2. [Object-Oriented Programming (OOP)](#object-oriented-programming-oop)
3. [SOLID Principles](#solid-principles)
4. [Design Patterns](#design-patterns)
5. [System Design Fundamentals](#system-design-fundamentals)

---

## Scalability & Architecture

### Q1: Why is horizontal scaling preferred over vertical scaling?
**Answer:**
- **Horizontal Scaling**: Adding more machines/nodes to distribute load
- **Vertical Scaling**: Adding more resources (CPU, RAM) to a single machine
- **Why Horizontal is Better**:
  - No single point of failure; if one server goes down, others handle traffic
  - Theoretically unlimited scalability
  - Cost-effective (commodity hardware)
  - Better fault tolerance and redundancy
  - Supports load balancing and distribution
- **Vertical Limitations**: Hardware limits, downtime during upgrades, single point of failure, expensive

### Q2: Why can highly coupled code become dangerous?
**Answer:**
- **Tight Coupling Issues**:
  - Changes in one module force changes in dependent modules (ripple effect)
  - Hard to test in isolation
  - Difficult to reuse components
  - Poor maintainability
  - Difficult to understand the system
  - High risk of introducing bugs during refactoring
- **Example**: Database directly linked to business logic → can't switch databases without rewriting logic
- **Solution**: Use abstractions, dependency injection, loose coupling

### Q3: Can a scalable system still be poorly maintainable?
**Answer:**
- **Yes, absolutely**. Scalability ≠ Maintainability
- **Scalable but Unmaintainable**: Microservices with no clear interfaces, poor documentation, inconsistent patterns
- **Maintainable but Not Scalable**: Well-structured monolith that doesn't distribute easily
- **Key Insight**: Both require separate efforts—architecture for scale, design for maintainability
- **Example**: Netflix scaled horizontally but required strong patterns (SOLID, clear boundaries) for maintainability

### Q4: Is caching an HLD topic or LLD topic?
**Answer:**
- **Both**, but in different contexts:
  - **HLD**: Caching strategy (Redis, CDN, cache layers between services)
  - **LLD**: Cache implementation details (LRU eviction, TTL, invalidation strategy)
- **HLD Focus**: Where to place caches, cache-aside vs write-through patterns, distributed cache systems
- **LLD Focus**: Data structure for cache, replacement algorithms, thread safety

### Q5: Why do companies separate services into microservices?
**Answer:**
- **Benefits**:
  - **Independent Scalability**: Scale only what needs scaling
  - **Technology Flexibility**: Different services can use different stacks
  - **Team Autonomy**: Different teams own different services
  - **Independent Deployment**: Deploy without coordinating with other teams
  - **Fault Isolation**: One service failure doesn't crash entire system
  - **Clear Boundaries**: Well-defined interfaces (APIs)
- **Trade-offs**: Increased complexity, distributed debugging, network latency, data consistency challenges

### Q6: Which matters more in HLD: algorithms or architecture?
**Answer:**
- **Architecture** matters more in HLD
  - HLD focuses on system structure, service boundaries, data flow
  - Algorithms are more LLD concerns
- **Why**: A well-architected system with average algorithms beats poorly-architected system with great algorithms
- **Analogy**: Architecture is the building blueprint; algorithms are construction techniques
- **However**: For specific domains (ML, gaming), algorithm choice significantly impacts HLD

---

## Object-Oriented Programming (OOP)

### Q7: Difference between abstraction and encapsulation?
**Answer:**
| Aspect | Abstraction | Encapsulation |
|--------|-------------|---------------|
| **Definition** | Hiding complex implementation details | Hiding internal state and exposing interface |
| **Focus** | "What does it do?" | "How does it do it?" |
| **Implementation** | Interfaces, abstract classes | Private/public access modifiers |
| **Example** | Car interface (start, stop, accelerate) | Car class with private engine details |
| **Purpose** | Reduce complexity | Data protection & bundling |

### Q8: What is runtime polymorphism and why do we need virtual functions?
**Answer:**
- **Runtime Polymorphism**: Method resolution happens at runtime, not compile time
- **Virtual Functions**: Allow derived classes to override base class methods
- **Mechanism**:
  ```cpp
  class Shape {
  public:
    virtual void draw() = 0;  // Virtual function
  };
  
  class Circle : public Shape {
  public:
    void draw() override { cout << "Drawing circle"; }
  };
  
  Shape* shape = new Circle();
  shape->draw();  // Calls Circle::draw() at runtime
  ```
- **Why Needed**:
  - Write generic code that works with base class pointers/references
  - Achieve abstraction and loose coupling
  - Enable strategy pattern and polymorphic behavior

### Q9: What happens internally when a virtual function is used?
**Answer:**
- **Virtual Table (VTable)**:
  - Each class with virtual functions has a VTable
  - VTable contains pointers to virtual function implementations
  - Each object maintains a pointer to its class's VTable (vptr)
- **Lookup Process**:
  ```
  1. Call shape->draw()
  2. Check object's vptr → points to Circle's VTable
  3. Look up draw() in Circle's VTable
  4. Call Circle::draw()
  ```
- **Cost**: Extra memory (vptr per object, VTable per class) + runtime lookup
- **Performance**: Minimal, but there IS overhead vs non-virtual

### Q10: Why is inheritance sometimes dangerous?
**Answer:**
- **Tight Coupling**: Child tightly bound to parent implementation
- **Fragile Base Class Problem**: Parent changes break children unexpectedly
- **LSP Violation**: Child might break parent's contracts
- **Multiple Inheritance Complexity**: Diamond problem, ambiguity
- **Over-engineering**: Using inheritance when composition is simpler
- **Example**: 
  ```cpp
  class Bird { virtual void fly() {} };
  class Penguin : public Bird {};  // Penguin can't fly! Breaks contract
  ```

### Q11: Why is composition preferred over inheritance?
**Answer:**
- **Composition**: "Has-a" relationship (object contains other objects)
- **Inheritance**: "Is-a" relationship (object is a type of another)
- **Advantages of Composition**:
  - More flexible and reusable
  - Avoids tight coupling
  - No fragile base class problem
  - Solves diamond problem naturally
  - Better code clarity
- **Example**:
  ```cpp
  // Inheritance (dangerous)
  class SportsCar : public Car, public Vehicle { };
  
  // Composition (better)
  class SportsCar {
    Engine engine;
    Transmission trans;
  };
  ```
- **Rule of Thumb**: Prefer composition; use inheritance only for "is-a" relationships

### Q12: What is data hiding?
**Answer:**
- **Definition**: Hiding internal object state from outside world
- **Mechanism**: Private/protected access modifiers
- **Benefits**:
  - Prevents unauthorized modification
  - Allows internal implementation changes without affecting external code
  - Enforces contracts and invariants
- **Example**:
  ```cpp
  class BankAccount {
  private:
    double balance;  // Hidden from outside
  public:
    void deposit(double amount) { /* validate then update */ }
  };
  ```

### Q13: What is the diamond problem?
**Answer:**
- **Scenario**:
  ```cpp
  class A { void func() {} };
  class B : public A {};
  class C : public A {};
  class D : public B, public C {};
  
  // D inherits from A twice - ambiguity!
  ```
- **Problem**: Which A::func() does D use?
- **Why Ambiguity Happens**:
  - Multiple inheritance paths to same base class
  - Compiler doesn't know which version to call
  - Duplicate member variables
- **Solutions**:
  1. **Virtual Inheritance**: `class B : virtual public A`
  2. **Explicit specification**: `d.B::func()`
  3. **Avoid multiple inheritance**

### Q14: How does virtual inheritance solve the diamond problem?
**Answer:**
- **Virtual Inheritance**: `class B : virtual public A`
- **Effect**: Only ONE copy of base class exists regardless of inheritance paths
- **How It Works**:
  ```cpp
  class A { };
  class B : virtual public A { };
  class C : virtual public A { };
  class D : public B, public C { };  // A exists once
  ```
- **Who Constructs Virtual Base Class**: Most derived class (D) is responsible
- **Trade-off**: Increases complexity, slight performance overhead

### Q15: Why is a giant class dangerous?
**Answer:**
- **Problems**:
  - Single Responsibility Principle violation
  - Hard to test (testing one feature requires whole class)
  - Difficult to maintain and understand
  - High coupling between unrelated features
  - Poor reusability
  - Increased chance of bugs
- **Example**: UserManager handling users, permissions, notifications, database
- **Solution**: Break into smaller, focused classes (SRP)

---

## SOLID Principles

### Q16: Which SOLID principle reduces tight coupling?
**Answer:**
- **Dependency Inversion Principle (DIP)** - most direct
  - Depend on abstractions, not concretions
  - High-level modules shouldn't depend on low-level modules
- **Also Helps**:
  - **Open/Closed Principle (OCP)**: Design for extension reduces coupling
  - **Interface Segregation Principle (ISP)**: Narrow interfaces reduce dependencies

### Q17: How does OCP (Open/Closed Principle) help scalability?
**Answer:**
- **OCP**: Open for extension, closed for modification
- **Scalability Connection**:
  - Add new features without modifying existing code
  - Reduces risk and regression testing
  - Enables new services/modules independently
- **Example**:
  ```cpp
  // Not OCP - need to modify for each new payment method
  if (type == "credit") { creditPay(); }
  else if (type == "debit") { debitPay(); }
  
  // OCP - extend with new PaymentProcessor
  class PaymentStrategy {
    virtual void pay() = 0;
  };
  ```

### Q18: Difference between SRP and ISP?
**Answer:**
| Aspect | SRP (Single Responsibility) | ISP (Interface Segregation) |
|--------|--------------------------|---------------------------|
| **Scope** | Classes | Interfaces |
| **Focus** | One reason to change | Clients shouldn't depend on methods they don't use |
| **Example** | UserService only handles users | Client-specific interfaces vs fat interface |
| **Problem Solved** | God classes | Forced dependencies |
| **Implementation** | Break large classes | Break large interfaces |

- **Relation**: Often go hand-in-hand; narrow interfaces naturally lead to single responsibilities

### Q19: Why do companies use interfaces heavily?
**Answer:**
- **Contracts**: Clear API contracts
- **Loose Coupling**: Depend on abstractions
- **Testability**: Easy to mock/stub
- **Flexibility**: Swap implementations easily
- **Evolution**: Add new implementations without breaking existing code
- **Microservices**: Service boundaries defined by interfaces
- **Example**: Database interface allows swapping MySQL ↔ PostgreSQL

### Q20: Why is dependency injection powerful?
**Answer:**
- **Definition**: Providing dependencies from outside rather than creating internally
- **Benefits**:
  - **Loose Coupling**: Object doesn't need to know how to create dependencies
  - **Testability**: Inject mocks for testing
  - **Flexibility**: Swap implementations at runtime
  - **Configuration**: Change behavior without code changes
- **Example**:
  ```cpp
  // Without DI (tightly coupled)
  class UserService {
    Database db = new MySQLDatabase();
  };
  
  // With DI (loosely coupled)
  class UserService {
    Database& db;  // Injected
    UserService(Database& database) : db(database) {}
  };
  ```

### Q21: Which SOLID principle is violated if child breaks parent behavior?
**Answer:**
- **Liskov Substitution Principle (LSP)**
- **Definition**: Derived classes must substitute base class without breaking contracts
- **Violation Example**:
  ```cpp
  class Bird { virtual void fly() {} };
  class Penguin : public Bird {  // Violates LSP!
    void fly() override { throw exception("Can't fly"); }
  };
  ```
- **Consequence**: Code expecting Bird::fly() breaks when passed Penguin

---

## Design Patterns

### Q22: Why is Strategy Pattern better than if-else chains?
**Answer:**
- **Traditional If-Else**:
  ```cpp
  if (paymentType == "credit") creditPay();
  else if (paymentType == "debit") debitPay();
  else if (paymentType == "paypal") paypalPay();
  // Adding new method requires modifying this code
  ```
- **Strategy Pattern**:
  ```cpp
  class PaymentStrategy { virtual void pay() = 0; };
  class CreditPayment : public PaymentStrategy { void pay() { /* ... */ } };
  
  processor.setStrategy(new CreditPayment());
  processor.process();  // Calls appropriate strategy
  ```
- **Advantages**:
  - **OCP**: Closed for modification, open for extension
  - **New Methods**: Just add new Strategy class
  - **Runtime Selection**: Switch strategies dynamically
  - **Testability**: Test each strategy independently

### Q23: Why is Strategy Pattern scalable?
**Answer:**
- **Easy to Extend**: New strategies don't require modifying core logic
- **Independent Development**: Different teams can implement different strategies
- **No Explosion of Classes**: vs inheritance hierarchy with multiple conditionals
- **Configuration-Driven**: Can load strategies from config files
- **Microservices Friendly**: Each strategy could be a service

### Q24: Why use Factory Pattern?
**Answer:**
- **Problem It Solves**:
  - Object creation scattered throughout code
  - Direct dependency on concrete classes
  - Difficult to switch implementations
- **Benefits**:
  - **Centralize Creation**: Single point of object creation
  - **Loose Coupling**: Code depends on factory interface, not concrete classes
  - **Flexibility**: Change creation logic without affecting client code
  - **Consistency**: Ensure objects are created correctly
- **When to Use**: When object creation is complex or might change

### Q25: Which SOLID principle does Factory Pattern support?
**Answer:**
- **Dependency Inversion Principle (DIP)** - primary
  - Depend on factory interface, not concrete classes
- **Open/Closed Principle (OCP)** - secondary
  - Add new product types without modifying existing code
- **Single Responsibility Principle (SRP)** - secondary
  - Separates creation logic from usage

### Q26: Difference between Factory Method and Abstract Factory?
**Answer:**
| Aspect | Factory Method | Abstract Factory |
|--------|---|---|
| **Creates** | Single product type | Family of related products |
| **Interface** | Single create method | Multiple create methods |
| **Use Case** | Simple object creation | Complex, multi-related objects |
| **Example** | `createPaymentProcessor()` | `createPaymentProcessor()`, `createLogger()`, `createDatabase()` |
| **Families** | Not concerned | Ensures consistency across families |

### Q27: Why centralize object creation (Factory Pattern)?
**Answer:**
- **Single Point of Change**: Modify creation logic in one place
- **Consistency**: All objects created the same way
- **Validation**: Centralized validation before creation
- **Caching**: Reuse objects if appropriate
- **Logging/Monitoring**: Track object creation
- **Example**: Database connection pooling vs creating new connection each time

### Q28: What problem occurs if object creation is scattered?
**Answer:**
- **Maintenance Nightmare**: Update creation logic everywhere
- **Inconsistency**: Different creation patterns in different places
- **Tight Coupling**: Depend on concrete classes throughout
- **Hard to Test**: Can't mock or control creation
- **Security Issues**: Validation logic duplicated and inconsistent
- **Scaling**: Adding new product types requires updating multiple locations

### Q29: Factory vs Strategy Pattern - Key Differences?
**Answer:**
| Aspect | Factory | Strategy |
|--------|---------|----------|
| **Purpose** | Object creation | Behavior selection |
| **When Used** | Creating objects | Executing algorithms |
| **Question Asked** | "How to create objects?" | "Which algorithm to use?" |
| **Relationship** | One object produced | Object behavior determined |
| **Example** | Create database connection | Choose payment algorithm |
| **Combination** | Often used together | Often used together |

### Q30: When should Abstract Factory be used?
**Answer:**
- **Scenarios**:
  1. **Cross-platform Systems**: Create platform-specific UI components
     ```cpp
     class UIFactory {
       virtual Button createButton() = 0;
       virtual TextField createTextField() = 0;
     };
     ```
  2. **Related Product Families**: Database + Connection Pool + Logger together
  3. **Ensuring Consistency**: Products work well together
- **Example**: Windows UI factory vs Mac UI factory
- **Benefit**: Ensures families of products are compatible

### Q31: Why are related product families important?
**Answer:**
- **Consistency**: Products designed to work together
- **Contract**: Guarantee compatibility
- **Example**: Windows Button, Windows TextField, Windows Menu (all look consistent)
- **Problem Solved**: Mixing Windows buttons with Mac menus looks wrong
- **Abstract Factory Ensures**: Only compatible families are combined

### Q32: Singleton Pattern - Why and How?
**Answer:**
- **Purpose**: Ensure only one instance of a class exists
- **Implementation**:
  ```cpp
  class Singleton {
  private:
    static Singleton* instance;
    Singleton() {}  // Private constructor
  public:
    static Singleton* getInstance() {
      if (instance == nullptr)
        instance = new Singleton();
      return instance;
    }
  };
  ```
- **Uses**: Logger, database connection, configuration manager
- **Why Private Constructor**: Prevent multiple instantiation
- **Why Delete Copy Constructor**: Prevent copying singleton

### Q33: Why does singleton break in multithreading?
**Answer:**
- **Problem**:
  ```cpp
  if (instance == nullptr)  // Thread A checks: null
                            // Thread B checks: null
    instance = new Singleton();  // Both create instance!
  ```
- **Race Condition**: Multiple threads create multiple instances
- **Solutions**:
  1. **Double-Checked Locking** (complex, error-prone)
  2. **Meyer's Singleton** (C++11 automatic thread-safe)
     ```cpp
     static Singleton& getInstance() {
       static Singleton instance;
       return instance;
     }
     ```
  3. **Eager Initialization**: Create at startup

### Q34: Difference between static class and singleton?
**Answer:**
| Aspect | Static Class | Singleton |
|--------|------------|-----------|
| **Instance** | None (all static) | One instance |
| **Inheritance** | Can't inherit | Can inherit |
| **State** | Shared globally | One instance with state |
| **Thread Safety** | Easier (no state) | Requires synchronization |
| **Testability** | Hard to mock | Easier to mock |
| **Lifetime** | Program lifetime | Controlled lifetime |
| **Use Case** | Utility functions | Shared resource |

### Q35: Why singleton can become anti-pattern?
**Answer:**
- **Hidden Dependencies**: Hard to see what a class depends on
- **Testability Issues**: Difficult to replace with mocks
- **Global State**: Violates principle of explicit dependencies
- **Thread Safety Complex**: Easy to get wrong
- **Lifetime Issues**: Hard to control when singleton is destroyed
- **Modern Alternative**: Dependency Injection
- **Modern Systems**: Prefer DI over singleton

### Q36: What problem does Observer Pattern solve?
**Answer:**
- **Problem**: One object changes → many objects need to know
- **Without Observer**:
  ```cpp
  // Bad: Subject knows about all observers
  class Subject {
    void change() {
      observer1.update();
      observer2.update();
      observer3.update();
    }
  };
  ```
- **With Observer**:
  ```cpp
  class Subject {
    vector<Observer*> observers;
    void notifyAll() {
      for (auto obs : observers)
        obs->update();
    }
  };
  ```
- **Benefit**: Subject doesn't know about specific observers (loose coupling)

### Q37: Why is Observer loosely coupled?
**Answer:**
- **Subject**: Depends on Observer interface, not concrete classes
- **Observers**: Don't know about each other
- **Dynamic**: Observers can be added/removed at runtime
- **Independent**: Each observer can change independently
- **Example**: Event system where listeners don't know about each other

### Q38: Difference between Observer and Pub-Sub?
**Answer:**
| Aspect | Observer | Pub-Sub |
|--------|----------|---------|
| **Communication** | Direct (synchronous) | Indirect (usually async) |
| **Intermediary** | None | Message broker |
| **Scope** | Single process | Distributed systems |
| **Coupling** | Loose but direct | Very loose |
| **Scalability** | Moderate | Highly scalable |
| **Example** | Button click → listeners | User event → message queue |

### Q39: Why is Observer useful in notifications?
**Answer:**
- **Decoupling**: Notification system doesn't know about subscribers
- **Dynamic**: Add/remove subscribers without changing notification code
- **Multiple Handlers**: One event triggers multiple actions
- **Example**:
  ```cpp
  class UserCreated : public Subject {
    void notify() {
      notifyAll();  // All observers (email, log, analytics) get notified
    }
  };
  ```

### Q40: Why are subscribers dynamic in Observer?
**Answer:**
- **Runtime Registration**: Subscribe/unsubscribe at runtime
- **Flexibility**: Add new subscribers without code changes
- **Adaptability**: System reacts to changing requirements
- **Scalability**: More subscribers = more processing, but same code
- **Testability**: Easily add test observers

### Q41: Decorator vs Inheritance - Key Differences?
**Answer:**
| Aspect | Decorator | Inheritance |
|--------|-----------|------------|
| **Relationship** | Wrapping | Extending |
| **Flexibility** | Runtime combinations | Compile-time |
| **Coupling** | Loosely coupled | Tightly coupled |
| **Code Explosion** | None | Exponential (class hierarchy) |
| **Example** | Decorating coffee with milk/sugar | Creating MilkCoffee class |
| **Problem Solved** | Too many class combinations | Inflexible hierarchies |

- **When to Use Decorator**: Want to add responsibilities dynamically
- **When to Use Inheritance**: True "is-a" relationship

### Q42: How does Least Knowledge Principle reduce coupling?
**Answer:**
- **Definition**: Only talk to immediate friends (don't reach through intermediaries)
- **Bad**:
  ```cpp
  person.getWallet().getMoney().withdraw();  // Chain of calls
  ```
- **Good**:
  ```cpp
  person.withdraw();  // Direct method
  ```
- **Benefits**:
  - Changes in wallet/money don't affect person's users
  - Fewer dependencies
  - More maintainable
- **Trade-off**: Sometimes creates more wrapper methods

### Q43: Difference between encapsulation and Least Knowledge Principle?
**Answer:**
| Aspect | Encapsulation | Least Knowledge |
|--------|---|---|
| **Focus** | Data hiding | Dependency hiding |
| **What** | Hide internal state | Hide navigation path |
| **Mechanism** | Private/public | Method aggregation |
| **Example** | Private variables | No chained calls |
| **Scope** | Within class | Between classes |

### Q44: Why do microservices naturally support Least Knowledge?
**Answer:**
- **Bounded Contexts**: Each service is self-contained
- **API Boundaries**: Only communicate through APIs
- **No Direct Access**: Can't peek into other service's database
- **Enforced**: Network boundaries enforce the principle
- **Result**: Services are loosely coupled by design

### Q45: Which design patterns support Least Knowledge?
**Answer:**
- **Facade Pattern**: Single interface to complex subsystem
- **Proxy Pattern**: Intermediary controls access
- **Adapter Pattern**: Adapts incompatible interfaces
- **Factory Pattern**: Hides creation complexity
- **Observer Pattern**: Indirect notification (if using event bus)

### Q46: Why is exposing internal objects risky?
**Answer:**
- **External Modification**: Outsiders can modify internal state
- **Unexpected Behavior**: Changes outside your control
- **Contract Violation**: Internal object can be in invalid state
- **Example**:
  ```cpp
  // Risky
  vector<Item>& getItems() { return items; }  // External can modify
  
  // Safe
  const vector<Item>& getItems() const { return items; }
  ```
- **Solution**: Return const references or copies

---

## System Design Fundamentals

### Q47: Why does Amazon prefer composition in their systems?
**Answer:**
- **Microservices Architecture**: Service composition vs inheritance
- **Independent Scaling**: Each service scales independently
- **Technology Diversity**: Different services use different tech stacks
- **Team Autonomy**: Teams own their services
- **Failure Isolation**: One service failure doesn't cascade
- **Evolution**: Easy to replace services

### Q48: How does Netflix handle thousands of services?
**Answer:**
- **Clear Service Boundaries**: Well-defined contracts
- **Resilience**: Circuit breakers, timeouts, retries
- **Monitoring**: Comprehensive observability
- **Automation**: Infrastructure as code
- **SOLID Principles**: Applied across services
- **Documentation**: Clear contracts and dependencies

### Q49: What makes Google's codebase maintainable at scale?
**Answer:**
- **Strict Conventions**: Enforced coding standards
- **Code Review**: Rigorous peer review
- **Testing**: Extensive test coverage
- **Documentation**: Well-documented code
- **Refactoring Culture**: Regular codebase improvement
- **Monorepo**: Single source of truth

### Q50: Why do APIs matter for system design?
**Answer:**
- **Contracts**: Clear agreements between services
- **Evolution**: Version APIs for backward compatibility
- **Documentation**: Self-documenting interfaces
- **Testing**: Test against contract
- **Loosening**: Enables independent deployment
- **Example**: REST, gRPC, GraphQL provide clear contracts

### Q51: Why is data consistency hard in distributed systems?
**Answer:**
- **CAP Theorem**: Can't have Consistency, Availability, Partition tolerance
- **Network Issues**: Partitions happen
- **Trade-offs**: Choose what matters most
  - Strong consistency: CP (Cassandra, HBase)
  - High availability: AP (DynamoDB, Riak)
- **Solutions**: Event sourcing, eventual consistency, distributed transactions

### Q52: When should you use NoSQL vs SQL?
**Answer:**
| Aspect | SQL | NoSQL |
|--------|-----|-------|
| **Schema** | Fixed | Flexible |
| **Consistency** | Strong (ACID) | Eventual |
| **Scalability** | Vertical | Horizontal |
| **Queries** | Complex joins | Simple lookups |
| **Use Case** | Financial systems | Real-time analytics |
| **Example** | PostgreSQL | MongoDB, DynamoDB |

### Q53: What is eventual consistency?
**Answer:**
- **Definition**: System eventually reaches consistent state (not immediately)
- **Trade-off**: Availability over immediate consistency
- **Example**: Updating Instagram profile picture
  - Write succeeds immediately
  - Propagates to other regions eventually
  - Users might see old pic briefly
- **When Acceptable**: Social media, caching, non-critical data
- **When Not**: Financial transactions, medical records

### Q54: Why is monitoring critical in distributed systems?
**Answer:**
- **Visibility**: Understand what's happening across services
- **Performance**: Identify bottlenecks
- **Debugging**: Trace requests across services
- **Alerting**: Detect problems before users do
- **Capacity**: Plan for growth
- **Example**: Distributed tracing (Jaeger, Datadog)

### Q55: How do circuit breakers improve system resilience?
**Answer:**
- **Purpose**: Prevent cascading failures
- **States**:
  - **Closed**: Normal operation
  - **Open**: Fail fast, don't call service
  - **Half-Open**: Test if service recovered
- **Benefit**: Protects system from repeated failures
- **Example**: If payment service fails, stop calling it until recovered

### Q56: What is the difference between load balancing and service discovery?
**Answer:**
| Aspect | Load Balancing | Service Discovery |
|--------|---|---|
| **Purpose** | Distribute traffic | Find service location |
| **When** | Request routing | Startup |
| **Examples** | Nginx, HAProxy | Consul, Eureka |
| **Problem** | Server overload | Service location changes |

### Q57: Why do some companies use event-driven architecture?
**Answer:**
- **Decoupling**: Services communicate through events, not direct calls
- **Scalability**: Easy to add new consumers of events
- **Resilience**: Producer doesn't care if consumer fails
- **Temporal Decoupling**: Services don't need to be online simultaneously
- **Example**: User signs up → triggers email, notification, analytics
- **Trade-off**: Complex debugging, eventual consistency

### Q58: What is idempotency and why is it important?
**Answer:**
- **Definition**: Same request multiple times has same result as once
- **Why Important**: Network failures cause retries
- **Without Idempotency**:
  ```cpp
  POST /transfer?from=A&to=B&amount=100
  // Retry causes double transfer!
  ```
- **With Idempotency**:
  ```cpp
  POST /transfer with idempotency_key=UUID
  // Retry returns same result, not double transfer
  ```
- **Implementation**: Track request IDs, check before processing

### Q59: What is graceful degradation?
**Answer:**
- **Definition**: System continues functioning with reduced functionality when components fail
- **Example**: 
  - Search service fails → show cached results
  - Recommendation service fails → show popular items
  - Image service fails → show text only
- **Goal**: Preserve core functionality even when not all systems work
- **Implementation**: Feature flags, fallbacks, defaults

### Q60: Why is version compatibility important in APIs?
**Answer:**
- **Problem**: Old clients still use old API versions
- **Solution Strategies**:
  - **URL Versioning**: `/v1/users`, `/v2/users`
  - **Header Versioning**: `Accept: application/vnd.api+json;version=2`
  - **Query Versioning**: `?version=2`
- **Backward Compatibility**: New version supports old clients
- **Deprecation**: Old versions sunset with notice
- **Example**: Facebook, Twitter, GitHub all version their APIs

---

## Quick Reference: Pattern Selection Guide

```
When choosing patterns:
├─ Creating Objects
│  ├─ Simple → Constructor
│  ├─ Complex → Factory Method
│  └─ Related Families → Abstract Factory
│
├─ Varying Behavior
│  ├─ Runtime choice → Strategy
│  ├─ Conditional setup → Builder
│  └─ Multiple algorithms → Strategy
│
├─ Loose Coupling
│  ├─ Between services → Pub-Sub
│  ├─ Within process → Observer
│  └─ Access control → Proxy
│
└─ Adding Functionality
   ├─ Runtime → Decorator
   ├─ Compile-time → Inheritance
   └─ Alternative interface → Adapter
```

---

## Interview Preparation Tips

1. **Understand Trade-offs**: Every pattern/principle has costs and benefits
2. **Real Examples**: Use real systems (Netflix, Amazon, Google) in answers
3. **Code Examples**: Prepare concise code snippets
4. **Scalability**: Always consider how pattern scales
5. **Alternatives**: Know when NOT to use a pattern
6. **Communication**: Explain concepts simply, then dive deep
