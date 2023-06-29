* README

Tiger Abstract Syntax Tree nodes with their principal members.
Incomplete classes are tagged with a `*'.

/Ast/               (Location location)
  /Dec/             (symbol name)
    FunctionDec     (VarChunk formals, NameTy result, Exp body)
      MethodDec     ()
    TypeDec         (Ty ty)
    VarDec          (NameTy type_name, Exp init)

  /Exp/             ()
    /Var/           ()
O     FieldVar      (symbol name)
      SimpleVar     (symbol name)
      SubscriptVar  (Var var, Exp index)

O   ArrayExp        (const location& location,ast::NameTy* type_name,ast::Exp* size,ast::Exp* init)
O   AssignExp       (SimpleVar svar, IntExp intexp)
O   BreakExp        ()
O   CallExp         (string s, exp e)
O   MethodCallExp
    CastExp         (Exp exp, Ty ty)
    ForExp          (VarDec vardec, Exp hi, Exp body)
O   IfExp           (Exp test, Exp body)
    IntExp          (int value)
O   LetExp          (ChunkList* chunks, Exp e)
    NilExp          ()
O   ObjectExp
    OpExp           (Exp left, Oper oper, Exp right)
O   RecordExp
O   SeqExp          (? Exp exp)
O   StringExp
    WhileExp        (Exp test, Exp body)

  /Ty/              ()
    ArrayTy         (NameTy base_type)
    ClassTy         (NameTy super, ChunkList chunks)
    NameTy          (symbol name)
O   RecordTy

  ChunkList         (list_type chunks)

  Field             (symbol name, NameTy type_name)

  FieldInit         (symbol name, Exp init)


Some of these classes also inherit from other classes.

/Escapable/
  VarDec            (NameTy type_name, Exp init)

/Typable/
  /Dec/             (symbol name)
  /Exp/             ()
  /Ty/              ()

/TypeConstructor/
  /Ty/              ()
  FunctionDec       (VarChunk formals, NameTy result, Exp body)
  NilExp            ()
  TypeDec           (Ty ty)

