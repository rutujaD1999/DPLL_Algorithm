#include<bits/stdc++.h>
using namespace std;
#define POS 1
#define NEG 2
#define BOTH 3
int checkClause(vector<vector<int>> clause, vector<int> model)
{
    int count=0,fcount=0;
    for(int i=0;i<clause.size();i++)
    {
        fcount=0;
        for(int  j=0;j<clause[i].size();j++)
        {
            if(clause[i][j]>0)
            {
                if(model[clause[i][j]]==1)
                {
                    count++;
                    break;
                }
                else if(model[clause[i][j]]==2)
                {
                    fcount++;
                }
            }
            else if(clause[i][j]<0)
            {
                if(model[abs(clause[i][j])]==2)
                {
                    count++;
                    break;
                }
                else if(model[abs(clause[i][j])]==1)
                {
                    fcount++;
                }
            }
        }
        if(fcount==clause[i].size())
        {
            return -1;
        }
    }
    if(count==clause.size())
    {
        return 1;
    }
    return 0;
}

int findPureSymbol(vector<int> sym)
{
    for(int i=0;i<sym.size();i++)
    {
        if(sym[i]==POS || sym[i]==NEG)
        {
            return i;
        }
    }
    return 0;
}

int findUnitClause(vector<vector<int>> clause,vector<int> sym)
{
    for(int i=0;i<clause.size();i++)
    {
        if(clause[i].size()==1 && sym[abs(clause[i][0])]!=0)
        {
            return i;
        }
    }
    return -1;
}

bool DPLL(vector<vector<int>> clause,vector<int> sym,vector<int> model)
{
	int checkClauseVal = checkClause(clause,model);
	if(checkClauseVal==1)
	{
		cout<<"MODEL FOUND!!!"<<endl;
		for(int i=0;i<model.size();i++)
		{
			if(model[i]!=0)
			{
				if(model[i]==1)
				{
					cout<<i<<" - "<<"True"<<endl;
				}
				else 
				{
					cout<<i<<" - "<<"False"<<endl;
				}
			}
		}
		cout<<endl;
		return true;
	}
	else if(checkClauseVal==-1)
	{
		//cout<<"returning false"<<endl;
		return false;
	}
	else
	{
		int p=findPureSymbol(sym);
		if(p!=0)
		{
			if(sym[p]==POS)
			{
				model[p]=1;
			}
			else
			{
				model[p]=2;
			}
			sym[p]=0;
			//cout<<"executed pure symbol : "<<p<<endl;
			bool ans=DPLL(clause,sym,model);
			if(ans)
			{
				return true;
			}
			
		}
		int uindex=findUnitClause(clause,sym);
		if(uindex>=0)
		{
			int u=clause[uindex][0];
			if(u>0)
			{
				model[u]=1;
			}
			else
			{
				model[abs(u)]=2;
			}
			sym[abs(u)]=0;
			//cout<<"executed unit clause : "<<u<<endl;
			bool ans=DPLL(clause,sym,model);
			if(ans)
			{
				return true;
			}
		}
		int i;
		for(i=1;i<sym.size();i++)
		{
			if(sym[i]!=0)
			{
				sym[i]=0;
				break;
			}
		}
		if(i<sym.size())
		{
			model[i]=1;
			//cout<<"calling with sym true : "<<i<<endl;
			bool a=DPLL(clause,sym,model);
			if(a)
			{
				return true;
			}
			model[i]=2;
			//cout<<"calling with sym false : "<<i<<endl;
			bool b=DPLL(clause,sym,model);
			if(b)
			{
				return true;
			}
			return false;
		}
		return false;
	}
}
		
	

int main()
{
    vector<vector<int>> clause;
    int nosym,noclause;
    cout<<"Enter no of symbols : ";
    cin>>nosym;
    cout<<"Enter no of clauses : ";
    cin>>noclause;
    vector<int> sym(nosym+1,0);
	vector<int> model(nosym+1,0);
    cout<<"Enter clause in each line : "<<endl;
    for(int i=0;i<noclause;i++)
    {
        int linesym;
        vector<int> temp;
        cout<<"No of entries in clause "<<i<<" : ";
        cin>>linesym;
        for(int j=0;j<linesym;j++)
        {
            int x;
            cin>>x;
            temp.push_back(x);
            if(x>0 && sym[x]==NEG)
            {
                sym[x]=BOTH;
            }
            else if(x<0 && sym[abs(x)]==POS)
            {
                sym[abs(x)]=BOTH;
            }
            else if(x>0 && sym[x]==0)
            {
            	sym[x]=POS;
            }
            else if(x<0 && sym[abs(x)]==0)
            {
            	sym[abs(x)]=NEG;
            }
        }
        clause.push_back(temp);
    }
/*
    for(int i=0;i<clause.size();i++)
    {
    	for(int j=0;j<clause[i].size();j++)
    	{
    		cout<<clause[i][j]<<" ";
    	}
    	cout<<endl;
    }
    cout<<"Symbols : "<<endl;
    for(int i=0;i<sym.size();i++)
    {
    	cout<<sym[i]<<" ";
    }
    cout<<endl;*/
    bool ans=DPLL(clause,sym,model);
    cout<<ans<<endl;
    return 0;
}
