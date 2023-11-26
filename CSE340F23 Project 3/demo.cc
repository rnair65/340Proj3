#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#include "lexer.h"

#include <unordered_map>
#include <stack>
#include <iostream>
#include <queue>

using namespace std;

struct InstructionNode * parse_generate_intermediate_representation();

void toPar();
void boPar();

InstructionNode* bodPars();
InstructionNode* assign_stmt();

ArithmeticOperatorType exCheck(TokenType operand);

bool opCheck(Token t);
bool primary(TokenType t);

InstructionNode* inPar();
InstructionNode* outPar();

ConditionalOperatorType getOp(TokenType t);

InstructionNode* ifPar();
InstructionNode* whilParle();

void syntax_error();

InstructionNode* getList(vector<InstructionNode*> vec);

void conPar(InstructionNode* node);

InstructionNode* forPar();
InstructionNode* swiPar();

void secIndSet(InstructionNode* node, Token t);
void firIndSet(InstructionNode* node, string storChec);

LexicalAnalyzer lexer;

unordered_map<string, int> map;
stack<string> puVa; 
string storChec[1000];

int pointer = 0;
string pres;
queue<int> bottoms;

unordered_map<string, int> maChec;
InstructionNode* lastOne;

vector<InstructionNode*> listNod;
unordered_map<InstructionNode*, InstructionNode*> branMa;

InstructionNode* ofTop;



int counter = 0;

struct InstructionNode * parse_generate_intermediate_representation()
{
    // Sample program for demonstration purpose only
    // Replace the following with a parser that reads the program from stdin &
    // creates appropriate data structures to be executed by execute_program()
    // This is the imaginary input for the following construction:
    
    // a, b, c, d;
    // {
    //     input a;
    //     input b;
    //     c = 10;
    // 
    //     IF c <> a
    //     {
    //         output b;
    //     }
    // 
    //     IF c > 1
    //     {
    //         a = b + 900;
    //         input d;
    //         IF a > 10
    //         {
    //             output d;
    //         }
    //     }
    // 
    //     d = 0;
    //     WHILE d < 4
    //     {
    //         c = a + d;
    //         IF d > 1
    //         {
    //             output d;
    //         }
    //         d = d + 1;
    //     }
    // }
    // 1 2 3 4 5 6

    // // Assigning location for variable "a"
    // int address_a = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for variable "b"
    // int address_b = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for variable "c"
    // int address_c = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for variable "d"
    // int address_d = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for constant 10
    // int address_ten = next_available;
    // mem[next_available] = 10;
    // next_available++;

    // // Assigning location for constant 1
    // int address_one = next_available;
    // mem[next_available] = 1;
    // next_available++;

    // // Assigning location for constant 900
    // int address_ninehundred = next_available;
    // mem[next_available] = 900;
    // next_available++;

    // // Assigning location for constant 3
    // int address_three = next_available;
    // mem[next_available] = 3;
    // next_available++;

    // // Assigning location for constant 0
    // int address_zero = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for constant 4
    // int address_four = next_available;
    // mem[next_available] = 4;
    // next_available++;

    // struct InstructionNode * i1 = new InstructionNode;
    // struct InstructionNode * i2 = new InstructionNode;
    // struct InstructionNode * i3 = new InstructionNode;
    // struct InstructionNode * i4 = new InstructionNode;
    // struct InstructionNode * i5 = new InstructionNode;
    // struct InstructionNode * i6 = new InstructionNode;
    // struct InstructionNode * i7 = new InstructionNode;
    // struct InstructionNode * i8 = new InstructionNode;
    // struct InstructionNode * i9 = new InstructionNode;
    // struct InstructionNode * i10 = new InstructionNode;
    // struct InstructionNode * i11 = new InstructionNode;
    // struct InstructionNode * i12 = new InstructionNode;
    // struct InstructionNode * i13 = new InstructionNode;
    // struct InstructionNode * i14 = new InstructionNode;
    // struct InstructionNode * i15 = new InstructionNode;
    // struct InstructionNode * i16 = new InstructionNode;
    // struct InstructionNode * i17 = new InstructionNode;
    // struct InstructionNode * i18 = new InstructionNode;
    // struct InstructionNode * i19 = new InstructionNode;
    // struct InstructionNode * i20 = new InstructionNode;
    // struct InstructionNode * i21 = new InstructionNode;
    // struct InstructionNode * i22 = new InstructionNode;

    // i1->type = IN;                                      // input a
    // i1->input_inst.var_index = address_a;
    // i1->next = i2;

    // i2->type = IN;                                      // input b
    // i2->input_inst.var_index = address_b;
    // i2->next = i3;

    // i3->type = ASSIGN;                                  // c = 10
    // i3->assign_inst.left_hand_side_index = address_c;
    // i3->assign_inst.op = OPERATOR_NONE;
    // i3->assign_inst.operand1_index = address_ten;
    // i3->next = i4;

    // i4->type = CJMP;                                    // if c <> a
    // i4->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
    // i4->cjmp_inst.operand1_index = address_c;
    // i4->cjmp_inst.operand2_index = address_a;
    // i4->cjmp_inst.target = i6;                          // if not (c <> a) skip forward to NOOP
    // i4->next = i5;

    // i5->type = OUT;                                     // output b
    // i5->output_inst.var_index = address_b;
    // i5->next = i6;

    // i6->type = NOOP;                                    // NOOP after IF
    // i6->next = i7;

    // i7->type = CJMP;                                    // if c > 1
    // i7->cjmp_inst.condition_op = CONDITION_GREATER;
    // i7->cjmp_inst.operand1_index = address_c;
    // i7->cjmp_inst.operand2_index = address_one;
    // i7->cjmp_inst.target = i13;                         // if not (c > 1) skip forward to NOOP (way down)
    // i7->next = i8;

    // i8->type = ASSIGN;                                  // a = b + 900
    // i8->assign_inst.left_hand_side_index = address_a;
    // i8->assign_inst.op = OPERATOR_PLUS;
    // i8->assign_inst.operand1_index = address_b;
    // i8->assign_inst.operand2_index = address_ninehundred;
    // i8->next = i9;

    // i9->type = IN;                                      // input d
    // i9->input_inst.var_index = address_d;
    // i9->next = i10;

    // i10->type = CJMP;                                   // if a > 10
    // i10->cjmp_inst.condition_op = CONDITION_GREATER;
    // i10->cjmp_inst.operand1_index = address_a;
    // i10->cjmp_inst.operand2_index = address_ten;
    // i10->cjmp_inst.target = i12;                        // if not (a > 10) skipp forward to NOOP
    // i10->next = i11;

    // i11->type = OUT;                                    // output d
    // i11->output_inst.var_index = address_d;
    // i11->next = i12;

    // i12->type = NOOP;                                   // NOOP after inner IF
    // i12->next = i13;

    // i13->type = NOOP;                                   // NOOP after outer IF
    // i13->next = i14;

    // i14->type = ASSIGN;                                 // d = 0
    // i14->assign_inst.left_hand_side_index = address_d;
    // i14->assign_inst.op = OPERATOR_NONE;
    // i14->assign_inst.operand1_index = address_zero;
    // i14->next = i15;

    // i15->type = CJMP;                                   // if d < 4
    // i15->cjmp_inst.condition_op = CONDITION_LESS;
    // i15->cjmp_inst.operand1_index = address_d;
    // i15->cjmp_inst.operand2_index = address_four;
    // i15->cjmp_inst.target = i22;                        // if not (d < 4) skip whole WHILE body
    // i15->next = i16;

    // i16->type = ASSIGN;                                 // c = a + d
    // i16->assign_inst.left_hand_side_index = address_c;
    // i16->assign_inst.op = OPERATOR_PLUS;
    // i16->assign_inst.operand1_index = address_a;
    // i16->assign_inst.operand2_index = address_d;
    // i16->next = i17;

    // i17->type = CJMP;                                   // if d > 1
    // i17->cjmp_inst.condition_op = CONDITION_GREATER;
    // i17->cjmp_inst.operand1_index = address_d;
    // i17->cjmp_inst.operand2_index = address_one;
    // i17->cjmp_inst.target = i19;                        // if not (d > 1) skip body of IF
    // i17->next = i18;

    // i18->type = OUT;                                    // output d
    // i18->output_inst.var_index = address_d;
    // i18->next = i19;

    // i19->type = NOOP;                                   // NOOP after body of IF
    // i19->next = i20;

    // i20->type = ASSIGN;                                 // d = d + 1
    // i20->assign_inst.left_hand_side_index = address_d;
    // i20->assign_inst.op = OPERATOR_PLUS;
    // i20->assign_inst.operand1_index = address_d;
    // i20->assign_inst.operand2_index = address_one;
    // i20->next = i21;

    // i21->type = JMP;
    // i21->jmp_inst.target = i15;
    // i21->next = i22;

    // i22->type = NOOP;                                   // NOOP after body of WHILE
    // i22->next = NULL;

    // // Inputs
    // inputs.push_back(1);
    // inputs.push_back(2);
    // inputs.push_back(3);
    // inputs.push_back(4);
    // inputs.push_back(5);
    // inputs.push_back(6);

    // return i1;
    for (int i = 0; i < 1000; i++) {

        mem[i] = 0;


    }

    toPar();
    ofTop = bodPars();
    

    boPar();

    return ofTop;
}

void toPar() {

    Token t = lexer.GetToken();
    int i = 0;

    while (t.token_type != SEMICOLON) {

        storChec[i] = t.lexeme;
        maChec.insert(make_pair(t.lexeme, i));
        i++;

        t = lexer.GetToken();
        if (t.token_type != SEMICOLON) t = lexer.GetToken();
    }
    
    pointer = i;


}

void boPar() {
    Token t = lexer.GetToken();

     while (t.token_type != END_OF_FILE) {

        inputs.push_back(stoi(t.lexeme));
        t = lexer.GetToken();

    }

}

InstructionNode* bodPars() {
  
  InstructionNode* get_node;
  InstructionNode* topBod;
  InstructionNode* pres_node;

  bool firsChec = true;
  bool forChec = false;
  bool switchChec = false;

    Token t = lexer.GetToken();
    if (t.token_type == LBRACE) {
        puVa.push("{");
    }
    else {
        syntax_error();
    }

    while (t.token_type != RBRACE) {

        t = lexer.GetToken();
    
        if(t.token_type==RBRACE) {
            break;
        }
        
        if (t.token_type == ID) {
            pres = t.lexeme;
            get_node = assign_stmt();

        } else if (t.token_type == INPUT) {
            get_node = inPar();

        } else if (t.token_type == OUTPUT) {
            get_node = outPar();

        } else if (t.token_type == IF) {
            get_node = ifPar();

        } else if (t.token_type == WHILE) {
            get_node = whilParle();

        } else if (t.token_type == FOR) {
            forChec = true;
            get_node = forPar();

        } else if (t.token_type == SWITCH) {
            switchChec = true;
            get_node = swiPar();
        
        }

        if(firsChec){
             if (switchChec) {

                switchChec = false;
                topBod = get_node; 
                InstructionNode* last = NULL; 

                for (InstructionNode* n = get_node->cjmp_inst.target; n != NULL; n=n->next) {
                    if (n->next == NULL) {

                        last = n;
                        break;

                    }
                }
                pres_node = last;
            } else if(forChec) {
                forChec = false;
                topBod = get_node;
                pres_node = topBod->next->cjmp_inst.target;

            } else if (get_node->type != CJMP) {

                topBod = get_node;
                topBod->next = NULL;
                pres_node = topBod;

            } else {
                topBod = get_node;
                pres_node = topBod->cjmp_inst.target;
                pres_node->next = NULL;
        }
            firsChec = false;

        } else {
             if(forChec) {

                pres_node->next = get_node;
                forChec = false;
                pres_node = get_node->next->cjmp_inst.target;

                
            } else if (switchChec) {

                switchChec = false;
                pres_node->next = get_node; 

                InstructionNode* last = NULL; 
                InstructionNode* n = get_node->cjmp_inst.target;
              

                while (n != NULL) {

                    if (n->next == NULL) {
                        last = n;
                        break;
                    }

                    n = n->next;

                }

                pres_node = last;

            } else if (get_node->type!=CJMP) {

                pres_node->next = get_node;
                pres_node = get_node;

                pres_node->next = NULL; //check
                pres_node->next = NULL;

            } else {
                pres_node->next = get_node;
                pres_node = get_node->cjmp_inst.target;

                pres_node->next = NULL;

            }
          
        }
      
    }

    InstructionNode* test = new InstructionNode;
    test = topBod;


    return topBod;

}

InstructionNode* assign_stmt() {
    
    InstructionNode* node = new InstructionNode;

    node->next = NULL;
    node->type = ASSIGN;

    bool stmtChec = false;
    int left_addr = maChec[pres];

    node->assign_inst.left_hand_side_index = left_addr;

    
    Token t = lexer.GetToken();

    if (t.token_type == EQUAL) {

        t = lexer.GetToken();

        if (primary(t.token_type) && !(opCheck(lexer.peek(1)))) {
            stmtChec = true;

            if (t.token_type == NUM) {

                node->assign_inst.op = OPERATOR_NONE;

                if (maChec.find(t.lexeme) != maChec.end()) {

                    node->assign_inst.operand1_index = maChec[t.lexeme];
                    mem[maChec[t.lexeme]] = stoi(t.lexeme);

                } else {
                    storChec[pointer] = t.lexeme;
                    maChec.insert(make_pair(t.lexeme, pointer));
                    pointer++;
                    node->assign_inst.operand1_index = maChec[t.lexeme];
                    mem[maChec[t.lexeme]] = stoi(t.lexeme);

                }
            } else if (t.token_type == ID) {
                node->assign_inst.operand1_index = maChec[t.lexeme];
               
            }
        } else if (primary(t.token_type) && (opCheck(lexer.peek(1)))) {  
            if (primary(t.token_type) && primary(lexer.peek(2).token_type)) { 
                if (t.token_type == ID) { 
                    int op1 = maChec[t.lexeme];
                    node->assign_inst.operand1_index = op1;

                } else {

                    if (maChec.find(t.lexeme) != maChec.end()) node->assign_inst.operand1_index = maChec[t.lexeme];
                    else {
                        storChec[pointer] = t.lexeme;
                        maChec.insert(make_pair(t.lexeme, pointer));
                        pointer++;

                        node->assign_inst.operand1_index = maChec[t.lexeme];
                        mem[maChec[t.lexeme]] = stoi(t.lexeme);

                    }

                }

                t = lexer.GetToken();
                TokenType op = t.token_type;
                t = lexer.GetToken();

                if (t.token_type == ID) {
                   int op2 = maChec[t.lexeme];
                   node->assign_inst.operand2_index = op2;
                } else {
                    if (maChec.find(t.lexeme) != maChec.end()) node->assign_inst.operand2_index = maChec[t.lexeme];
                    else {
                        storChec[pointer] = t.lexeme;
                        maChec.insert(make_pair(t.lexeme, pointer));
                        pointer++;

                        node->assign_inst.operand2_index = maChec[t.lexeme];
                        mem[maChec[t.lexeme]] = stoi(t.lexeme);
                    }
                }
                ArithmeticOperatorType type = exCheck(op);
                node->assign_inst.op = type;
            } 
        }

        if(stmtChec){

            node->assign_inst.op = OPERATOR_NONE;
        }

        t = lexer.GetToken();

        if (t.token_type != SEMICOLON) {

            std::cout << "SYNTAX ERROR (NOT SEMICOLON) ON: " << t.lexeme << endl;
            syntax_error();

        }

    } else {
        std::cout << "error on: " << endl;
        syntax_error();

    }
 
    return node;

}

ArithmeticOperatorType exCheck(TokenType operand) {
    if (operand == PLUS) {
        return OPERATOR_PLUS;

    } else if (operand == MINUS) {
        return OPERATOR_MINUS;

    } else if (operand == MULT) {
        return OPERATOR_MULT;

    } else {
        return OPERATOR_DIV;

    }

}

bool opCheck(Token t) {
    if (t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT || t.token_type == DIV) {
        return true;

    } 

    return false;

}



bool primary(TokenType t) {

    if (t == ID || t == NUM) {

        return true;

    }

    return false;

}


InstructionNode* inPar() {

    InstructionNode* node = new InstructionNode;

    node->type = IN;
    node->next = NULL;

    Token t = lexer.GetToken();

    int vindex = maChec[t.lexeme];

    node->input_inst.var_index = vindex;

    return node;
    
}


InstructionNode* outPar() {
    InstructionNode* node = new InstructionNode;

    node->type = OUT;
    node->next = NULL;

    Token t = lexer.GetToken();

    if (t.token_type != ID) syntax_error();

    int vindex = maChec[t.lexeme];

    node->input_inst.var_index = vindex;
    listNod.push_back(node);

    return node;
}

ConditionalOperatorType getOp(TokenType t) {

    if (t == NOTEQUAL) {
        return CONDITION_NOTEQUAL;


    } else if (t == GREATER) {
        return CONDITION_GREATER;

    } else if (t == LESS) {
        return CONDITION_LESS;

    } else {
        cout << "failed operator";
        syntax_error();

    }
}

InstructionNode* ifPar() {

    InstructionNode* node = new InstructionNode;
    InstructionNode* target = new InstructionNode;

    node->next = NULL;
    target->type = NOOP;

    target->next = NULL;
    node->type = CJMP;

    conPar(node);

    node->next = bodPars();

    InstructionNode* last = NULL;

    for (InstructionNode* n = node; n != NULL; n=n->next) {

        if (n->next == NULL) {
            last = n;
            break;

        }
    }

    last->next = target;
    node->cjmp_inst.target = target;

    return node;
}

void conPar(InstructionNode* node) {

    Token t = lexer.GetToken();

    if (t.token_type == ID) { 
        node->cjmp_inst.operand1_index = maChec[t.lexeme];
  
    } else {
        if (maChec.find(t.lexeme) != maChec.end()) node->assign_inst.operand1_index = maChec[t.lexeme];
        else {
            storChec[pointer] = t.lexeme;
            maChec.insert(make_pair(t.lexeme, pointer));
            pointer++;
            node->cjmp_inst.operand1_index = maChec[t.lexeme];
        }
    }

    t = lexer.GetToken();
    node->cjmp_inst.condition_op = getOp(t.token_type);
    t = lexer.GetToken();

    if (t.token_type == ID) {

        node->cjmp_inst.operand2_index = maChec[t.lexeme];

    } else {

        if (maChec.find(t.lexeme) != maChec.end()) {
            node->assign_inst.operand2_index = maChec[t.lexeme];
        } else {
     
            storChec[pointer] = t.lexeme;
    
            maChec.insert(make_pair(t.lexeme, pointer));
            pointer++;

            node->cjmp_inst.operand2_index = maChec[t.lexeme];
            mem[maChec[t.lexeme]] = stoi(t.lexeme);

        }
    }
}

InstructionNode* whilParle() {

    InstructionNode* node = new InstructionNode;
    InstructionNode* target = new InstructionNode;
    InstructionNode* back = new InstructionNode;

    node->next = NULL;
    node->type = CJMP;

    target->type = NOOP;
    target->next = NULL;

    back->type = JMP;
    conPar(node);
 
 
    node->next = bodPars();
 
    InstructionNode* last = NULL;
    for (InstructionNode* n = node; n != NULL; n=n->next) {
        
        if (n->next == NULL) {
            last = n;
            break;

        }
    }

    last->next = back;
    node->cjmp_inst.target = target;

    back->jmp_inst.target = node;
    back->next = target;

    return node;
}

InstructionNode* forPar() {

    InstructionNode* init = new InstructionNode; //init
    InstructionNode* cond = new InstructionNode; 
    InstructionNode* back = new InstructionNode; 
    InstructionNode* inc = new InstructionNode; 
    InstructionNode* target = new InstructionNode;

    target->type = NOOP;
    target->next = NULL;
    back->type = JMP;

    Token t = lexer.GetToken (); 
    t = lexer.GetToken(); 

    pres = t.lexeme;

    init = assign_stmt(); 
    init->next = cond;

    cond->type = CJMP;

    conPar(cond);

    t = lexer.GetToken();
    t = lexer.GetToken(); 

    pres = t.lexeme;

    inc = assign_stmt();
    t = lexer.GetToken(); 
    cond->next = bodPars();

    InstructionNode* last = NULL;

    for (InstructionNode* n = cond; n != NULL; n=n->next) {

        if (n->next == NULL) {
            last = n;
            break;

        }
    }

    cond->cjmp_inst.target = target;
    back->jmp_inst.target = cond;

    last->next = inc;

    inc->next = back;
    back->next = target;

    InstructionNode* counter = init;
    int itcounter = 0;

    while (counter != NULL) {

        itcounter++;
        counter = counter->next;
        

    }  

    return init;
}

InstructionNode* swiPar() {

    InstructionNode* target = new InstructionNode;

    target->type = NOOP;
    target->next = NULL;

    InstructionNode* switch_head = NULL;
    InstructionNode* lastOne = NULL;

    Token t = lexer.GetToken();

    string storChec = t.lexeme; 
    stack<string> stack; 
    t = lexer.GetToken(); 
    int num = 0; 

    if (t.token_type == LBRACE) stack.push("{");

    while (!stack.empty()) {

        t = lexer.GetToken(); 

        if (t.token_type == CASE) {
            InstructionNode* node = new InstructionNode;

            node->type = CJMP;
            firIndSet(node, storChec);

            node->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
            t = lexer.GetToken(); 

            num = stoi(t.lexeme);
            secIndSet(node, t); 

            t = lexer.GetToken(); 
            node->cjmp_inst.target = bodPars();

            if (lastOne == NULL) {
                lastOne = node;
                switch_head = node;

            } else {
                lastOne->next = node;
                lastOne = lastOne->next;

            }

            InstructionNode* last = NULL;

            for (InstructionNode* n = node->cjmp_inst.target; n != NULL; n=n->next) {
                if (n->next == NULL) {

                    last = n;
                    break;

                }
            }

            last->next = target;
        } else if (t.token_type == DEFAULT) {

            t = lexer.GetToken(); 
            lastOne->next = bodPars();

            InstructionNode* last = NULL;

            for (InstructionNode* n = lastOne; n != NULL; n=n->next) {

                if (n->next == NULL) {
                    last = n;
                    break;

                }
            }

            last->next = target;
        } else {
            cout << "here syntax error lol" << endl;
            syntax_error();

        }

        if (lexer.peek(1).token_type == RBRACE) {
            t = lexer.GetToken();
            stack.pop();
            break;

        }

    }
    return switch_head;

}


void syntax_error() {
    std::cout << "SYNTAX ERROR";

}

InstructionNode* getList(vector<InstructionNode*> vec) {

    InstructionNode* ofTop = vec[0];
    InstructionNode* pres = ofTop;

    for (int i = 1; i < listNod.size(); i++) {
        pres->next = vec[i];
        pres = pres->next;
    }

    return ofTop;

}

/***/
void secIndSet(InstructionNode* node, Token t) {

    if (maChec.find(t.lexeme) != maChec.end()) node->assign_inst.operand2_index = maChec[t.lexeme];
        
        else {
            storChec[pointer] = t.lexeme; 
            maChec.insert(make_pair(t.lexeme, pointer));
            pointer++;
            node->cjmp_inst.operand2_index = maChec[t.lexeme];
            mem[maChec[t.lexeme]] = stoi(t.lexeme);

        }

}

void firIndSet(InstructionNode* node, string storChec) {

    node->assign_inst.operand1_index = maChec[storChec];

}

