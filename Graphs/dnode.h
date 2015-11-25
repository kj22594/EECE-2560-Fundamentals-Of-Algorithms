//
//  dnode.h
//  path
//
//  Created by Waleed Meleis on 1/7/15.
//  Copyright (c) 2015 Waleed Meleis. All rights reserved.
//

#ifndef path_dnode_h
#define path_dnode_h

class dnode
{
public:
   dnode(){};
   dnode(int i, int w);
   void setIndex(int i);
   void setWeight (int w) {weight = w;}
   void setPred (int p) {pred = p;}
   int getIndex();
   int getWeight() {return weight;}
   int getPred() {return pred;}
   dnode &operator=(dnode d);
   
private:
   int index;
   int weight;
   int pred;
};

dnode::dnode(int i, int w)
{
   index = i;
   weight = w;
}

void dnode::setIndex(int i) 
{
   index = i;
}

int dnode::getIndex()
{
   return index;
}

dnode &dnode::operator=(dnode d)
{
   setIndex(d.getIndex());
   setWeight(d.getWeight());
   setPred(d.getPred());
   
   return *this;
}

bool operator<(dnode d1, dnode d2)
{
   return d1.getWeight() < d2.getWeight();
}

bool operator>(dnode d1, dnode d2)
{
   return d1.getWeight() > d2.getWeight();
}

ostream &operator<<(ostream &ostr, dnode &d)
// Print all information about the dnode
{
   cout << d.getIndex() << " " << d.getWeight() << " " << d.getPred() << endl;
   
   return ostr;
}


#endif
