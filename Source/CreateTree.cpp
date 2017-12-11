#include "../Header/CreateTree.h"

using namespace std;

//-------------------------------------------------------------ROOT---------------------------------------------------------

tree<Lexeme*> createTree(list<Lexeme*>& lex)
{
	tree<Lexeme*> tr;
	tree<Lexeme*>::pre_order_iterator top=tr.begin();
	tree<Lexeme*>::pre_order_iterator root,childroot;
	Lexeme* l=new Lexeme("_root",0,NON_DEFINI);
	root=tr.insert(top,l);

	cout << "Tree Root" << endl;

	list<Lexeme*>::iterator itr;
	for(itr=lex.begin(); itr!=lex.end(); itr++)
	{
		switch((*itr)->getType())
		{
			case ARCHITECTURE:
				constructTreeOnArchitecture(tr,root,lex,itr);
				break;
			case ENTITY:
				constructTreeOnEntity(tr,root,lex,itr);
				break;
			case LIBRARY:
				constructTreeOnLibrary(tr,root,lex,itr);
				break;
			case PACKAGE:
				constructTreeOnPackage(tr,root,lex,itr);
				break;
			case USE:
				constructTreeOnUse(tr,root,lex,itr);
				break;
			default:
				break;
		}
	}
	return tr;
}

//-------------------------------------------------------------ARCHITECTURE---------------------------------------------------------
void constructTreeOnAffectationSignal(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& affectation, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Affectation Signal" << endl;
	itr--;	//Pour reperer l'operateur aff
	list<Lexeme*>::iterator itrAff, itrSource;
	tree<Lexeme*>::pre_order_iterator childaffectation,searchOpAff,searchOpSource;
	string typeAff,typeSource;
	//int taille_ref,taille_test; //Tester la taille des vecteurs
	bool source_set=false;
	bool aff_set=false;
	while((*itr)->getType()!=AFFECTATION_END)
	{
		switch((*itr)->getType())
		{
            		case OPERATOR_AFF:
		            	searchOpAff=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
				if(searchOpAff!=tr.end())
				{
					//Test préliminaire :est-ce un signal ou un port ?
					if((*searchOpAff)->getType()!=SIGNAL_ID&&(*searchOpAff)->getType()!=PORT_ID)
					{
						cout << "Erreur : operateur non valide ligne " << (*itr)->getLigne() << endl;
						return;
					}
					itrAff=itr;
					aff_set=true;
				}
				break;
			case OPERATOR_SOURCE:
		            	searchOpSource=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
				if(searchOpSource!=tr.end())
				{
					itrSource=itr;
					source_set=true;
				}
				break;
			default:
				break;
		}
		itr++;
	}

    	if(source_set)
    	{
		if(aff_set)
		{
			typeAff=findType(tr,searchOpAff);
			typeSource=findType(tr,searchOpSource);
			if(typeAff=="")
			{
			    cout << "Erreur d'affectation : type non trouve sur " << (*searchOpAff)->getLex() 
				<< " ligne " << (*searchOpAff)->getLigne() << endl;
			    return;
			}
			if(typeSource=="")
			{
			    cout << "Erreur d'affectation : type non trouve sur " << (*searchOpSource)->getLex() 
				<< " ligne " << (*searchOpSource)->getLigne() << endl;
			    return;
			}
			if(typeAff!=typeSource)
			{
			    cout << "Erreur d'affectation : types non identiques ligne " << (*itr)->getLigne() << endl;
			    return;
			}

			//A placer : tests taille vecteurs

			//Tous les tests sont passés
			childaffectation=tr.append_child(affectation,*itrAff);
			childaffectation=tr.append_child(affectation,*itrSource);			
		}
		else
		{
			cout << "Erreur : pas d'operateur affecte ligne " << (*itr)->getLigne() << endl;
		}
	}
	else
	{
		cout << "Erreur : pas d'operateur source ligne " << (*itr)->getLigne() << endl;
	}
}

void constructTreeOnAffectationVariable(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& affectation, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Affectation Variable" << endl;
	itr--;	//Pour reperer l'operateur aff
	list<Lexeme*>::iterator itrAff, itrSource;
	tree<Lexeme*>::pre_order_iterator childaffectation,searchOpAff,searchOpSource;
	string typeAff,typeSource;
	//int taille_ref,taille_test; //Tester la taille des vecteurs
	bool source_set=false;
	bool aff_set=false;
	while((*itr)->getType()!=AFFECTATION_END)
	{
		switch((*itr)->getType())
		{
            		case OPERATOR_AFF:
		            	searchOpAff=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
				if(searchOpAff!=tr.end())
				{
					//Test préliminaire :est-ce une varaible ?
					if((*searchOpAff)->getType()!=VARIABLE_ID)
					{
						cout << "Erreur : operateur non valide ligne " << (*itr)->getLigne() << endl;
						return;
					}
					itrAff=itr;
					aff_set=true;
				}
				break;
			case OPERATOR_SOURCE:
		            	searchOpSource=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
				if(searchOpSource!=tr.end())
				{
					itrSource=itr;
					source_set=true;
				}
				break;
			default:
				break;
		}
		itr++;
	}

    	if(source_set)
    	{
		if(aff_set)
		{
			typeAff=findType(tr,searchOpAff);
			typeSource=findType(tr,searchOpSource);
			if(typeAff=="")
			{
			    cout << "Erreur d'affectation : type non trouve sur " << (*searchOpAff)->getLex() 
				<< " ligne " << (*searchOpAff)->getLigne() << endl;
			    return;
			}
			if(typeSource=="")
			{
			    cout << "Erreur d'affectation : type non trouve sur " << (*searchOpSource)->getLex() 
				<< " ligne " << (*searchOpSource)->getLigne() << endl;
			    return;
			}
			if(typeAff!=typeSource)
			{
			    cout << "Erreur d'affectation : types non identiques ligne " << (*itr)->getLigne() << endl;
			    return;
			}

			//A placer : tests taille vecteurs

			//Tous les tests sont passés
			childaffectation=tr.append_child(affectation,*itrAff);
			childaffectation=tr.append_child(affectation,*itrSource);			
		}
		else
		{
			cout << "Erreur : pas d'operateur affecte ligne " << (*itr)->getLigne() << endl;
		}
	}
	else
	{
		cout << "Erreur : pas d'operateur source ligne " << (*itr)->getLigne() << endl;
	}
}

void constructTreeOnArchitecture(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architecture, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Architecture" << endl;

	tree<Lexeme*>::pre_order_iterator childarchi;
	while((*itr)->getType()!=ARCHITECTURE_END)
	{
		switch((*itr)->getType())
		{
			case ARCHITECTURE_ID:
				childarchi=tr.append_child(architecture,*itr);
				constructTreeOnArchitectureID(tr,childarchi,l,itr);
				break;
			default:
               	 		itr++;
				break;
		}
	}
}

void constructTreeOnArchitectureID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& architectureid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Architecture ID" << endl;

	tree<Lexeme*>::pre_order_iterator childarchiid;
	while((*itr)->getType()!=ARCHITECTURE_END)
	{
		switch((*itr)->getType())
		{
        		case AFFECTATION_SIGNAL:
            			childarchiid=tr.append_child(architectureid,*itr);
            			constructTreeOnAffectationSignal(tr,childarchiid,l,itr);
				break;
        		case AFFECTATION_VARIABLE:
            			childarchiid=tr.append_child(architectureid,*itr);
            			constructTreeOnAffectationVariable(tr,childarchiid,l,itr);
				break;
		    	case PROCESS:
		        	childarchiid=tr.append_child(architectureid,*itr);
		        	constructTreeOnProcess(tr,childarchiid,l,itr);
		        	break;
              		case PROCESS_ID:
		        	childarchiid=tr.append_child(architectureid,*itr);
		        	constructTreeOnProcess(tr,childarchiid,l,itr);
		        	break;
			case SIGNAL:
				constructTreeOnSignal(tr,architectureid,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnSignal(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signal, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Signal" << endl;

	tree<Lexeme*>::pre_order_iterator childsignal;
	while((*itr)->getType()!=SIGNAL_END)
	{
		switch((*itr)->getType())
		{
			case SIGNAL_ID:
                		childsignal=tr.append_child(signal,*itr);
				constructTreeOnSignalID(tr,childsignal,l,itr);
				break;
			default:
			    itr++;
				break;
		}
	}
}

void constructTreeOnSignalID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& signalid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Signal ID" << endl;

	tree<Lexeme*>::pre_order_iterator childsignalid;
	while((*itr)->getType()!=SIGNAL_END)
	{
		switch((*itr)->getType())
		{
			case SIGNAL_TYPE:
                		childsignalid=tr.append_child(signalid,*itr);
				break;
			case TYPE_VECTOR:
                		childsignalid=tr.append_child(signalid,*itr);
				constructTreeOnVector(tr,childsignalid,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

//-------------------------------------------------------------ENTITY---------------------------------------------------------

void constructTreeOnEntity(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entity, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Entity" << endl;

	tree<Lexeme*>::pre_order_iterator childentity;
	while((*itr)->getType()!=ENTITY_END)
	{
		switch((*itr)->getType())
		{
			case ENTITY_ID:
				childentity=tr.append_child(entity,*itr);
				constructTreeOnEntityID(tr,childentity,l,itr);
				break;
			default:
			    itr++;
				break;
		}
	}
}

void constructTreeOnEntityID(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& entityid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Entity ID" << endl;

	tree<Lexeme*>::pre_order_iterator childentityid;
	while((*itr)->getType()!=ENTITY_END)
	{
		switch((*itr)->getType())
		{
   			case GENERIC:
				childentityid=tr.append_child(entityid,*itr);
				constructTreeOnGeneric(tr,childentityid,l,itr);
				break;
			case PORT:
				childentityid=tr.append_child(entityid,*itr);
				constructTreeOnPort(tr,childentityid,l,itr);
				break;
			default:
				itr++;
				break;
		}
	}
}

void constructTreeOnGeneric(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& generic, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Generic" << endl;

	tree<Lexeme*>::pre_order_iterator childgeneric;
	while((*itr)->getType()!=GENERIC_END)
	{
		switch((*itr)->getType())
		{
			case GENERIC_ID:
				childgeneric=tr.append_child(generic,*itr);
				constructTreeOnGenericId(tr,childgeneric,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnGenericId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& genericid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Generic ID" << endl;

	tree<Lexeme*>::pre_order_iterator childgenericid;
	while((*itr)->getType()!=GENERIC_ID_END)
	{
		switch((*itr)->getType())
		{
			case GENERIC_TYPE:
				childgenericid=tr.append_child(genericid,*itr);
				break;
			case TYPE_VECTOR:
				childgenericid=tr.append_child(genericid,*itr);
				constructTreeOnVector(tr,childgenericid,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnPort(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& port, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Port" << endl;

	tree<Lexeme*>::pre_order_iterator childport;
	while((*itr)->getType()!=PORT_END)
	{
		switch((*itr)->getType())
		{
			case PORT_ID:
				childport=tr.append_child(port,*itr);
				constructTreeOnPortId(tr,childport,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnPortId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& portid, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Port ID" << endl;

	tree<Lexeme*>::pre_order_iterator childportid;
	while((*itr)->getType()!=PORT_ID_END)
	{
		switch((*itr)->getType())
		{
			case PORT_IN:
				childportid=tr.append_child(portid,*itr);
				break;
			case PORT_INOUT:
				childportid=tr.append_child(portid,*itr);
				break;
			case PORT_OUT:
				childportid=tr.append_child(portid,*itr);
				break;
			case PORT_TYPE:
				childportid=tr.append_child(portid,*itr);
				break;
			case TYPE_VECTOR:
				childportid=tr.append_child(portid,*itr);
				constructTreeOnVector(tr,childportid,l,itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

//-------------------------------------------------------------LIBRARY---------------------------------------------------------

//Pour l'instant ne stocke rien : c'est use qui se charge de stocker la bonne librairie
void constructTreeOnLibrary(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Library" << endl;

	tree<Lexeme*>::pre_order_iterator childlibrary;
	while((*itr)->getType()!=LIBRARY_END)
	{
		switch((*itr)->getType())
		{
			case LIBRARY_ID:
				childlibrary=tr.append_child(library,*itr);
				break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnUse(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& library, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Use" << endl;

	tree<Lexeme*>::pre_order_iterator childuse,buf,library_id;
	buf=library;
	bool defineLibraryId=false;
	while((*itr)->getType()!=USE_END)
	{
		switch((*itr)->getType())
		{
			case LIBRARY_ID:
				if(!defineLibraryId)
				{
				    library_id=findLexemeInTree(tr.begin(),tr.end(),(*itr)->getLex());
				    if(library_id!=tr.end())
                    {
				    	buf=library_id;
                        defineLibraryId=true;
                    }
                    else
                    {
                        cout << "Erreur : librairie " << (*itr)->getLex() << " non trouvee" << endl;
                    }
				}
				break;
			case USE_ID:
				if(defineLibraryId)
				{
		            		childuse=tr.append_child(buf,*itr);
		            		buf=childuse;
				}
				else
				{
				    cout << "Erreur : identifiant librairie non trouvee" << endl;
				}
                		break;
			default:
				break;
		}
		itr++;
	}
}


//-------------------------------------------------------------PACKAGE---------------------------------------------------------

void constructTreeOnComponentId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& componentid, list<Lexeme*>& l, list<Lexeme*>::iterator &itr)
{
	cout << "Tree Component ID" << endl;

	tree<Lexeme*>::pre_order_iterator childcomponentid;
	while((*itr)->getType()!=COMPONENT_END)
	{
		switch((*itr)->getType())
		{
   			case GENERIC:
				childcomponentid=tr.append_child(componentid,*itr);
				constructTreeOnGeneric(tr,childcomponentid,l,itr);
				break;
			case PORT:
				childcomponentid=tr.append_child(componentid,*itr);
				constructTreeOnPort(tr,childcomponentid,l,itr);
				break;
			default:
                		itr++;
				break;
		}
	}
}

void constructTreeOnPackage(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& package, list<Lexeme*>& l, list<Lexeme*>::iterator &itr)
{
	cout << "Tree Package" << endl;

	tree<Lexeme*>::pre_order_iterator childpackage;
	while((*itr)->getType()!=PACKAGE_END)
	{
		switch((*itr)->getType())
		{
			case PACKAGE_ID:
				childpackage=tr.append_child(package,*itr);
                		constructTreeOnPackageId(tr,childpackage,l,itr);
				break;
			default:
                		itr++;
				break;
		}
	}
}

void constructTreeOnPackageId(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& packageid, list<Lexeme*>& l, list<Lexeme*>::iterator &itr)
{
	cout << "Tree Package ID" << endl;

	tree<Lexeme*>::pre_order_iterator childpackageid;
	while((*itr)->getType()!=PACKAGE_END)
	{
		switch((*itr)->getType())
		{
			case COMPONENT_ID:
				childpackageid=tr.append_child(packageid,*itr);
                		constructTreeOnComponentId(tr,childpackageid,l,itr);
				itr++; //temporaire
				break;
			default:
                		itr++;
				break;
		}
	}
}

//-------------------------------------------------------------PROCESS---------------------------------------------------------

tree<Lexeme*>& constructTreeForCondLogic(list<Lexeme*>& l, list<Lexeme*>::iterator& itr, int type_fin)
{
	cout << "Tree Condition" << endl;

	tree<Lexeme*> buf_conditions;
	tree<Lexeme*>::pre_order_iterator top_buf=buf_conditions.begin(),bufroot;
	Lexeme* bufLexeme = new Lexeme("root_condition", (*itr)->getLigne(), CONDITION_LOGIC);	//Temp
	bufroot=buf_conditions.insert(top_buf,bufLexeme);

	list<Lexeme*>::iterator begin_condition=itr;

	tree<Lexeme*>::pre_order_iterator childcondition;
	while((*itr)->getType()!=type_fin)
	{
		switch((*itr)->getType())
		{
			case CONDITION_LOGIC:
				childcondition=buf_conditions.append_child(bufroot,*itr);
				itr++;					//On passe au Lexeme suivant avant de construire un nouvel arbre
				buf_conditions.insert_subtree(childcondition,constructTreeForCondLogic(l,itr,type_fin));	//Temp ?
					//Traîte uniquement les conditions logiques après celle détectée : elles seront placées en enfant
				break;
/*
			case CONDITION_SCALAR:
				childcondition=buf_conditions.append_child(bufroot,*itr);
				itr++;					//On passe au Lexeme suivant avant de construire un nouvel arbre
			//	insert_subtree(childcondition,constructTreeForCondScalar(l,itr,type_fin));	//Temp ?
				break;
//			case IF_PARENTHESE_OUV:						//Je ne traite pas les parenthèses pour l'instant
//				constructTreeForCondition(l,itr,IF_PARENTHESE_FER);	
//				break;
*/
			default:
                		itr++;
				break;
		}
	}

	printTree(buf_conditions);
	return buf_conditions;
}


//A compléter
tree<Lexeme*>& constructTreeForOperand(list<Lexeme*>& l, list<Lexeme*>::iterator& itr, int type_fin)
{
	cout << "Tree Operand" << endl;

	tree<Lexeme*> buf_operand;
	tree<Lexeme*>::pre_order_iterator top_buf=buf_operand.begin(),bufroot;
	Lexeme* bufLexeme = new Lexeme("root_operand", (*itr)->getLigne(), OPERATOR_IF);	//Temp
	bufroot=buf_operand.insert(top_buf,bufLexeme);

	list<Lexeme*>::iterator&::begin_operand=itr;

	tree<Lexeme*>::pre_order_iterator childoperand;
	while((*itr)->getType()!=type_fin)
	{
		switch((*itr)->getType())
		{

		}
	}

	printTree(buf_conditions);
	return buf_conditions;
}

void constructTreeOnIf(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& _if, list<Lexeme*>& l, list<Lexeme*>::iterator &itr)
{
	cout << "Tree If" << endl;

	tree<Lexeme*> buf_conditions;
	tree<Lexeme*>::pre_order_iterator top_buf=buf_conditions.begin();
	tree<Lexeme*>::pre_order_iterator bufroot,bufchild;
	Lexeme* bufLexeme = new Lexeme("root_conditions_if", (*itr)->getLigne(), CONDITION);
	bufroot=buf_conditions.insert(top_buf,bufLexeme);
	
	list<Lexeme*>::iterator mem_if=itr;

	tree<Lexeme*>::pre_order_iterator childif;
	while((*itr)->getType()!=IF_END)
	{
		switch((*itr)->getType())
		{
			case ELSE:
				childif=tr.append_child(_if,*itr);
                		constructTreeOnIfInst(tr,childif,l,itr);
				break;
			case ELSIF:
				childif=tr.append_child(_if,*itr);
                		constructTreeOnIfInst(tr,childif,l,itr);
				break;
			case THEN:
				childif=tr.append_child(_if,*itr);
				constructTreeOnIfInst(tr,childif,l,itr);
				break;
			default:
                		itr++;
				break;
		}
	}

	childif=tr.insert_subtree(childif,constructTreeForCondLogic(l,mem_if,IF_END));
}

void constructTreeOnIfInst(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& if_inst, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree If Instructions" << endl;

    	itr++;
	tree<Lexeme*>::pre_order_iterator childifinst;
	while((*itr)->getType()!=IF_END&&(*itr)->getType()!=ELSE&&(*itr)->getType()!=ELSIF)
	{
		switch((*itr)->getType())
		{
        		case AFFECTATION_SIGNAL:
                		childifinst=tr.append_child(if_inst,*itr);
            			constructTreeOnAffectationSignal(tr,childifinst,l,itr);
				break;
        		case AFFECTATION_VARIABLE:
                		childifinst=tr.append_child(if_inst,*itr);
            			constructTreeOnAffectationVariable(tr,childifinst,l,itr);
				break;
            		case IF:
                		childifinst=tr.append_child(if_inst,*itr);
				constructTreeOnIf(tr,childifinst,l,itr);
                		break;
			default:
				break;
		}
		itr++;
	}
}

void constructTreeOnProcess(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Process" << endl;

	tree<Lexeme*>::pre_order_iterator childprocess;

	while((*itr)->getType()!=PROCESS_END)
	{
		switch((*itr)->getType())
		{
            		case PROCESS_BEGIN:
                		childprocess=tr.append_child(process,*itr);
				constructTreeOnProcessInst(tr,childprocess,l,itr);
                		break;
				break;
            		case PROCESS_SENSIBILITY:
                		childprocess=tr.append_child(process,*itr);
                        itr++;
				break;
			default:
                itr++;
				break;
		}
	}
}

void constructTreeOnProcessInst(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& process_inst, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
	cout << "Tree Process Instructions" << endl;

	tree<Lexeme*>::pre_order_iterator childprocessinst;
	while((*itr)->getType()!=PROCESS_END)
	{
		switch((*itr)->getType())
		{
        		case AFFECTATION_SIGNAL:
            			childprocessinst=tr.append_child(process_inst,*itr);
            			constructTreeOnAffectationSignal(tr,childprocessinst,l,itr);
				break;
        		case AFFECTATION_VARIABLE:
            			childprocessinst=tr.append_child(process_inst,*itr);
            			constructTreeOnAffectationVariable(tr,childprocessinst,l,itr);
				break;
            		case IF:
                		childprocessinst=tr.append_child(process_inst,*itr);
				constructTreeOnIf(tr,childprocessinst,l,itr);
                		break;
			default:
				break;
		}
		itr++;
	}
}

//-------------------------------------------------------------AUTRES---------------------------------------------------------


void constructTreeOnVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator& vec, list<Lexeme*>& l, list<Lexeme*>::iterator& itr)
{
    cout << "Tree Vector" << endl;

	tree<Lexeme*>::pre_order_iterator childvec;
	while((*itr)->getType()!=TYPE_VECTOR_END)
	{
		switch((*itr)->getType())
		{
		    case TYPE_VECTOR_BEGIN:
		        childvec=tr.append_child(vec,*itr);
		        break;
		    case TYPE_VECTOR_SENSE:
		        childvec=tr.append_child(vec,*itr);
		        break;
		    case TYPE_VECTOR_END:
		        childvec=tr.append_child(vec,*itr);
               		break;
		    default:
			break;
		}
		itr++;
	}

	if((*itr)->getType()==TYPE_VECTOR_END)
		childvec=tr.append_child(vec,*itr);
}

//-------------------------------------------------------------FIND---------------------------------------------------------

tree<Lexeme*>::pre_order_iterator findLexemeInTree(tree<Lexeme*>::pre_order_iterator begin_search, tree<Lexeme*>::pre_order_iterator end_search, string lexeme)
{
    tree<Lexeme*>::pre_order_iterator result=begin_search;
    while(result!=end_search)
    {
        if((*result)->getLex()==lexeme)
        {
            return result;
        }
        result++;
    }
    return end_search;
}

int findSizeOnVector(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator parent)
{
    tree<Lexeme*>::leaf_iterator searchSize;
    int debut=0;
    int fin=0;
    bool downto=false;
    for(searchSize=tr.begin_leaf(parent);searchSize!=tr.end_leaf(parent);searchSize++)
    {
         switch((*searchSize)->getType())
        {
            case TYPE_VECTOR_BEGIN:
                debut=stoi((*searchSize)->getLex());
                break;
            case TYPE_VECTOR_SENSE:
                if((*searchSize)->getLex()=="downto")
                    downto=true;
                break;
            case TYPE_VECTOR_END:
                fin=stoi((*searchSize)->getLex());
                break;
        }
    }
    if(downto)
        return debut-fin;

    return fin-debut;
}

string findType(tree<Lexeme*>& tr, tree<Lexeme*>::pre_order_iterator parent)
{
    tree<Lexeme*>::leaf_iterator searchType;
    for(searchType=tr.begin_leaf(parent);searchType!=tr.end_leaf(parent);searchType++)
    {
        switch((*searchType)->getType())
        {
            case PORT_TYPE:
                return (*searchType)->getLex();
            case SIGNAL_TYPE:
                return (*searchType)->getLex();
	    case TYPE_VECTOR:
                return (*searchType)->getLex();
            case VARIABLE_TYPE:
                return (*searchType)->getLex();
        }
    }
    return "";
}

//-------------------------------------------------------------PRINT---------------------------------------------------------

void printTree(tree<Lexeme*> tr)
{
	tree<Lexeme*>::pre_order_iterator itr=tr.begin();
	if(itr!=tr.end())
		++itr;

	while(itr!=tr.end())
	{
		for(int i=0; i<tr.depth(itr); i++)
		{
			cout << " ";
		}
		cout << (*itr)->getLex() << endl;
		++itr;
	}
}

int saveTree(tree<Lexeme*> tr, string libraryname)
{
	ofstream fichier(libraryname, ios::out | ios::trunc);
	if(!fichier)
	{
		cout << "Erreur a l'ecriture de " << libraryname << endl;
		return 0;
	}
	tree<Lexeme*>::pre_order_iterator itr=tr.begin();
	if(itr!=tr.end())
		++itr;

	while(itr!=tr.end())
	{

		for(int i=0; i<tr.depth(itr); i++)
		{
			fichier << "	";
		}
		fichier << (**itr);
		++itr;
	}

	return 1;
}
