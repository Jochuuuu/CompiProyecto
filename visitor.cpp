#include <iostream>
#include "exp.h"
#include "visitor.h"
#include <unordered_map>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}
int IFExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}
int NumberExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int BoolExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int IdentifierExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int AssignStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FCallStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int PrintStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int IfStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int WhileStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int CommentStatment::accept(Visitor *visitor)
{
    visitor->visit(this);

    return 0;
}
int ForStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int VarDec::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int VarDecList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}
int StatementList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}
int Body::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int Program::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FunDec::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FunDecList::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int ReturnStatement::accept(Visitor *visitor)
{
    visitor->visit(this);
    return 0;
}

int FCallExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

///////////////////////////////////////////////////////////////////////////////////

int PrintVisitor::visit(BinaryExp *exp)
{
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(NumberExp *exp)
{
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(BoolExp *exp)
{
    if (exp->value)
        cout << "true";
    else
        cout << "false";
    return 0;
}

int PrintVisitor::visit(IdentifierExp *exp)
{
    cout << exp->name;
    return 0;
}

void PrintVisitor::visit(AssignStatement *stm)
{
    printIndent();

    cout << stm->id << " := ";
    stm->rhs->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStatement *stm)
{
    printIndent();

    cout << "writeln(";

    short tm = 0;

    for (auto f : stm->e)
    {
        if (tm >= 1)
        {
            cout << ",";
        }
        f->accept(this);
        tm++;
    }

    //   stm->e->accept(this);
    cout << ");";
}

void PrintVisitor::visit(CommentStatment *stm)
{
    cout << stm->inicio;
    cout << stm->id;
    if (stm->inicio == "{")
    {
        cout << "}";
    }
    else if (stm->inicio == "(*")
    {
        cout << "*)";
    }
}

void PrintVisitor::visit(IfStatement *stm)
{
    cout << "if ";
    stm->condition->accept(this);
    cout << " then" << endl;
    printIndent();

    stm->then->accept(this);
    if (stm->els)
    {
        printIndent();
        cout << endl;
        printIndent();
        cout << "end" << endl;
        printIndent();
        cout << "else" << endl;
        printIndent();

        stm->els->accept(this);
        printIndent();
        cout << endl;
        printIndent();
        cout << "end;" << endl;
    }
    else
    {
        printIndent();
        cout << "end;" << endl;
    }
}

void PrintVisitor::imprimir(Program *program)
{
    cout << "Program " << program->nombre << ";" << endl;
    program->accept(this);
}

void PrintVisitor::visit(UsesList *stm)
{
    if (!stm) {return;}

    if (stm->uist.size() > 0)
    {
        printIndent();

        cout << "uses ";

        for (auto i : stm->uist)
        {
            printIndent();
            cout << i;
            if (i != stm->uist.back())
            {
                cout << ", ";
            }
        }
        cout << ";" << endl;
    }
};

void PrintVisitor::visit(Program *program)
{
    program->uses->accept(this);
    program->vardecs->accept(this);
    program->fundecs->accept(this);
};

int PrintVisitor::visit(IFExp *pepito)
{
    cout << "ifexp(";
    pepito->cond->accept(this);
    cout << ",";
    pepito->left->accept(this);
    cout << ",";
    pepito->right->accept(this);
    cout << ")";
    return 0;
}

void PrintVisitor::visit(WhileStatement *stm)
{
    cout << "while ";
    stm->condition->accept(this);
    cout << " do" << endl;
    printIndent();
    // cout << "begin" << endl;
    stm->b->accept(this);
    printIndent();
    cout << "end;";
}

void PrintVisitor::visit(ForStatement *stm)
{
    cout << "for ";

    cout << stm->start->id << " := ";
    stm->start->rhs->accept(this);

    //  stm->start->accept(this);
    if (stm->downto)
    {    cout << " downto ";
} else {    cout << " to ";}
    stm->end->accept(this);
    cout << " do" << endl;

    // cout << "  begin" << endl;
    printIndent();

    stm->b->accept(this);

    cout << endl;
    printIndent();

    cout << "end;";
}

void PrintVisitor::visit(VarDec *stm)
{
    // cout << "var ";
    // cout << stm->type;
    cout << " ";
    for (auto i : stm->vars)
    {
        cout << i;
        if (i != stm->vars.back())
            cout << ", ";
    }
    cout << " : " << stm->type;
    cout << ";";
}

void PrintVisitor::visit(VarDecList *stm)
{
    if (stm->vardecs.size() > 0)
    {
        printIndent();

        cout << "var " << endl;
    }
    for (auto i : stm->vardecs)
    {
        printIndent();
        i->accept(this);
        cout << endl;
    }

    if (stm->vardecs.size() > 0)
    {
        printIndent();
    }
}

void PrintVisitor::visit(StatementList *stm)
{
    bool anterior = false;
    for (auto i : stm->stms)
    {
        if (anterior && i->comentario == false)
        {
            cout << endl;
        }

        printIndent();
        i->accept(this);
        anterior = true;
    }
}

void PrintVisitor::visit(Body *stm)
{
    increaseIndent();
    stm->vardecs->accept(this);

    cout << "begin" << endl;
    stm->slist->accept(this);
    decreaseIndent();
}

void PrintVisitor::visit(FunDec *stm)
{

    if (stm->rtype == "void")
    {
        if (stm->fname != "main")
        {
            cout << "procedure" << " " << stm->fname << "(";
        }
    }
    else
    {
        cout << "function" << " " << stm->fname << "(";
    }
    currentFunction = stm->fname;
    bool first = true;
    list<string>::iterator type, name;
    for (type = stm->types.begin(), name = stm->vars.begin(); type != stm->types.end(); type++, name++)
    {
        if (!first)
            cout << ", ";
        cout << *type << " " << *name;
        first = false;
    }

    if (stm->rtype != "void")
    {
        cout << ") : " << (stm->rtype == "int" ? "integer" : stm->rtype) << endl;
    }
    else
    {
        if (stm->fname != "main")
        {
            cout << ")" << endl;
        }
    }
    stm->body->accept(this);
    cout << endl
         << "end";
    cout << (stm->fname == "main" ? "." : ";");

    currentFunction = "";
}

void PrintVisitor::visit(FunDecList *stm)
{
    for (auto i : stm->flist)
    {
        i->accept(this);
        cout << endl
             << endl;
    }
}

void PrintVisitor::visit(ReturnStatement *s)
{
    if (currentFunction.empty())
    {
        cout << "Error: 'return' fuera de contexto de función." << endl;
        exit(1);
    }

    cout << currentFunction << " := ";
    if (s->e != NULL)
    {
        s->e->accept(this);
    }
    cout << ";";
    return;
}

int PrintVisitor::visit(FCallExp *e)
{
    cout << e->fname << "(";
    list<Exp *>::iterator it;
    bool first = true;
    for (it = e->args.begin(); it != e->args.end(); ++it)
    {
        if (!first)
            cout << ",";
        first = false;
        (*it)->accept(this);
    }
    cout << ')';
    return 0;
}

void PrintVisitor::visit(FCallStatement *e)
{
    cout << e->fname << "(";
    list<Exp *>::iterator it;
    bool first = true;
    for (it = e->args.begin(); it != e->args.end(); ++it)
    {
        if (!first)
            cout << ",";
        first = false;
        (*it)->accept(this);
    }
    cout << ')';
}

void PrintVisitor::printIndent()
{
    for (int i = 0; i < indentLevel * 2; i++)
    {
        cout << ' ';
    }
}

///////////////////////////////////////////////////////////////////////////////////
