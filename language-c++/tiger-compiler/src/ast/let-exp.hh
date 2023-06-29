/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
  /// LetExp.
  class LetExp : public Exp
  {
  public:
    // FIXME: Some code was deleted here.
    LetExp(const Location&, ChunkList* chunks, Exp* body);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;

    ~LetExp() override;

    void accept(ConstVisitor& v) const override;

    void accept(Visitor& v) override;

    const Exp& body_get() const;
    Exp& body_get();
    const ChunkList& chunks_get() const;
    ChunkList& chunks_get();

  protected:
    ChunkList* chunks_;
    Exp* body_;
  };
} // namespace ast
#include <ast/let-exp.hxx>
