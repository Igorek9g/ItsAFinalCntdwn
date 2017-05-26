//
// Created by idalov on 10.05.17.
//

#include <Action.hh>
#include <PrimaryPat.hh>

void Action::Build()const {
   SetUserAction(new PrimaryPat);
}