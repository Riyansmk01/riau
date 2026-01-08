# Why Riau Exists

## The Problem

Modern web development faces a paradox:

**PHP** is everywhere, easy to deploy, but carries decades of legacy baggage.  
**Node.js** is fast and modern, but requires complex tooling.  
**Python** is elegant, but CGI deployment is clunky.  
**Go** is performant, but overkill for simple scripts.

**What if we could have the best of all worlds?**

---

## The Vision

**Riau** is designed to be:

### 1. **As Easy as PHP**
- Drop a `.riau` file on your server
- No compilation step for deployment
- CGI-ready out of the box
- Environment variables just work

### 2. **As Safe as Rust**
- Null safety built-in from day one
- Type inference prevents bugs
- No manual memory management
- Memory-safe by design

### 3. **As Modern as TypeScript**
- Clean, readable syntax
- Arrow functions
- Type annotations (optional)
- First-class functions

### 4. **As Fast as Go**
- Bytecode compilation
- Efficient VM execution
- Minimal runtime overhead
- Performance-first design

---

## The Philosophy

### **Simplicity Without Sacrifice**

```riau
// This is all you need for a web app
print("Content-Type: text/html\n\n")
print("<h1>Hello, World!</h1>")
```

No frameworks. No build tools. No configuration files. **Just code.**

### **Safety Without Ceremony**

```riau
// Null safety that doesn't get in your way
let user? = findUser(id)
if user {
    print(user.name)  // Guaranteed safe
}
```

The compiler prevents bugs **before** they happen.

### **Performance Without Complexity**

```riau
// Compiled to bytecode, executed in VM
// Faster than interpreted languages
// Simpler than compiled languages
```

You get speed **without** the complexity of C++ or Rust.

---

## The Target

Riau is **not** trying to replace:
- ❌ React for frontend
- ❌ Kubernetes for orchestration
- ❌ PostgreSQL for databases

Riau **is** perfect for:
- ✅ **CGI scripts** - The best CGI scripting language
- ✅ **Microservices** - Small, focused services
- ✅ **APIs** - RESTful endpoints
- ✅ **Automation** - System scripts with web interfaces
- ✅ **Prototyping** - Quick ideas to production

---

## The Killer Feature

### **Best-in-Class CGI Scripting**

While the world moved to complex frameworks, **CGI never died**. It's still:
- Simple to deploy
- Easy to understand
- Universally supported
- Perfect for small services

But existing CGI languages have problems:
- **PHP**: Legacy baggage, inconsistent API
- **Perl**: Dying ecosystem
- **Python**: Slow CGI mode
- **Bash**: Not designed for web

**Riau fixes all of this.**

```riau
// Modern CGI with zero configuration
let method = env("REQUEST_METHOD")
let query = env("QUERY_STRING")

print("Content-Type: application/json\n\n")
print("{")
print("  \"method\": \"" + method + "\",")
print("  \"query\": \"" + query + "\"")
print("}")
```

Clean. Safe. Fast. **Perfect.**

---

## The Roadmap

### **v0.1.x - Foundation** (Current)
- ✅ Core language features
- ✅ CGI support
- ✅ Enhanced error messages
- ✅ Performance tools

### **v0.2.x - Web Ready**
- 🔄 POST data handling
- 🔄 JSON parsing
- 🔄 Cookie & session support
- 🔄 String manipulation

### **v0.3.x - Database & I/O**
- 🔄 Database drivers (MySQL, PostgreSQL, SQLite)
- 🔄 File I/O operations
- 🔄 Template engine
- 🔄 WebSocket support

### **v1.0.x - Production**
- 🔄 JIT compilation
- 🔄 Package manager
- 🔄 Debugger
- 🔄 Production case studies

---

## The Promise

**Riau will always be:**

1. **Simple** - No build tools, no frameworks, just code
2. **Safe** - Null safety and type checking built-in
3. **Fast** - Bytecode VM, optimized execution
4. **Stable** - Semantic versioning, backward compatibility
5. **Open** - MIT license, community-driven

**Riau will never be:**

1. ❌ A PHP clone
2. ❌ A "batteries included" framework
3. ❌ A language with breaking changes
4. ❌ Proprietary or closed-source

---

## The Call to Action

### **For Developers**
If you're tired of:
- Complex build pipelines
- Framework churn
- Deployment headaches
- Null pointer exceptions

**Try Riau.**

### **For Contributors**
If you want to:
- Build a language from scratch
- Learn compiler design
- Shape the future of web scripting

**Join us.**

### **For Enterprises**
If you need:
- Simple, maintainable code
- Fast deployment cycles
- Reliable, safe execution
- Long-term stability

**Evaluate Riau.**

---

## The Bottom Line

**Riau exists because web development should be simple again.**

Not "simple" like "limited."  
Not "simple" like "toy language."  
**Simple** like "I can understand this in 5 minutes and ship it in 10."

That's the promise.  
That's the vision.  
**That's Riau.**

---

**Ready to try?**

```bash
git clone https://github.com/yourusername/riau
cd riau
.\build.bat
.\bin\riau.exe examples\web_hello.riau
```

**Welcome to the future of CGI scripting.** 🚀

---

**Version**: 0.1.1  
**Status**: Experimental Production Language  
**License**: MIT  
**Tagline**: *The Best CGI Scripting Language*
