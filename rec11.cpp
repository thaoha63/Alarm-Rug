/*
  rec11.cpp
  Tingting Min
  11/11/22.
  Starting code 21F
 */

#include <iostream>
#include <Vector>
using namespace std;
class Instrument{
public:
    virtual void makeSound() const = 0;
    virtual void normalPlay() const = 0;
};

void Instrument::makeSound() const {
    cout<<"To make a sound...";
}


class Brass : public Instrument{
public:
    Brass(int mouthPiece):mouthPiece(mouthPiece){}
    void makeSound() const override{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size "<<mouthPiece<<endl;
    }
private:
    int mouthPiece;
};
class Trumpet : public Brass{
    using Brass::Brass;
    void normalPlay() const override { cout << "Toot"; }
};
class Trombone : public Brass{
    using Brass::Brass;
    void normalPlay() const override{cout << "Blat";}
};


class String : public Instrument{
public:
    String(int pitch):pitch(pitch){}
    void makeSound() const override{
        Instrument :: makeSound();
        cout <<"bow a string with pitch "<<pitch<<endl;
    }
private:
    int pitch;
};
class Violin : public String{
    using String :: String;
    void normalPlay() const override{cout << "Screech";}
};
class Cello : public String{
    using String :: String;
    void normalPlay() const override{cout << "Squawk";}
};


class Percussion : public Instrument{
    //using Instrument::Instrument;
    void makeSound() const override{
        Instrument :: makeSound();
        cout << "hit me!"<<endl;
    }
};
class Drum : public Percussion{
    //using Percussion :: Percussion;
    void normalPlay() const override { cout << "Boom"; }
};
class Cymbal : public Percussion{
    //using Percussion :: Percussion;
    void normalPlay() const override { cout << "Crash"; }
};


class MILL{
public:
    void receiveInstr(Instrument& instr){
        instr.makeSound();
        for(Instrument*& instrp : inventory){
            if(!instrp){
                instrp = &instr;
                return;
            }
        }
        inventory.push_back(&instr);
    }

    void dailyTestPlay() const{
        for(Instrument* instrp : inventory){
            if(instrp){
                instrp->makeSound();
            }
        }
    }

    Instrument* loanOut(){
        for(Instrument*& instrp : inventory){
            if(instrp){
                Instrument* tempInstrp = instrp;
                instrp = nullptr;
                return tempInstrp;
            }
        }
        return nullptr;
    }
private:
    vector<Instrument*> inventory;
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cout << "have no instr\n";
    }

    void play()const{
        if(instr){
            instr->normalPlay();
        }
    }

private:
    Instrument* instr;
};

class Orch{
public:
    void addPlayer(Musician& member){
        members.push_back(&member);
    }
    void play()const{
        for(Musician* member: members){
            member->play();
        }
        cout <<endl;
    }
private:
    vector<Musician*> members;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ----------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;

    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
     MILL mill;

    cout << "Put the instruments into the MILL ------------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);

    cout << "Daily test -----------------------------------------------------\n"
         << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

    cout << "Define some Musicians-------------------------------------------\n";
     Musician harpo;
     Musician groucho;

     cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();
     cout << endl;
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << endl << endl;

     groucho.testPlay();
     cout << endl;
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     harpo.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";

     // fifth
     mill.receiveInstr(*groucho.giveBackInstr());
     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
     mill.receiveInstr(*harpo.giveBackInstr());


     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

     cout << endl;


    //
    // PART TWO
    //


    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

}