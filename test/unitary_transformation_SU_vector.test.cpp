#include <iostream>
#include <SQuIDs/SUNalg.h>
#include <iostream>

int main(){
  using squids::SU_vector;
  
  int dim=6;
  int Ngenerators=dim*dim;
  double th=1.456;
  double dl=1.231;
  double t=3.456;

  //Check that the time evolution is unitary
  for(unsigned int i=0;i<Ngenerators;i++){
    for(unsigned int j=0;j<Ngenerators;j++){
      SU_vector v1=SU_vector::Generator(dim,i);
      SU_vector v2=SU_vector::Generator(dim,j);
      double sprod=v1*v2;
      for(unsigned int it=0;it<dim;it++){
        SU_vector v3=SU_vector::Projector(dim,it);
        double out=sprod-v1.Evolve(v3,t)*v2.Evolve(v3,t);
        if(fabs(out)>1e-15){
          std::cout << "Generators: " << i << "  " << j << "  Evolution Operator: " << it <<
            "  \t" << out  << std::endl;
        }
      }
    }
  }

  //Check that the rotations are unitary transformations
  for(unsigned int i=0;i<Ngenerators;i++){
    for(unsigned int j=0;j<Ngenerators;j++){
      SU_vector v1=SU_vector::Generator(dim,i);
      SU_vector v2=SU_vector::Generator(dim,j);
      double sprod=v1*v2;
      for(unsigned int ir=1;ir<dim;ir++){
        for(unsigned int jr=ir+1;jr<dim;jr++){
          double out=sprod-v1.Rotate(ir,jr,th,dl)*v2.Rotate(ir,jr,th,dl);
          if(fabs(out)>1e-15){
            std::cout << "Generators: " << i << "  " << j << "  Rotation: " << ir << "  " << jr <<
              "  \t" << out  << std::endl;
          }
        }
      }
    }
  }

  for(unsigned int i=0;i<Ngenerators;i++){
    for(unsigned int j=0;j<Ngenerators;j++){
      for(unsigned int k=0;k<Ngenerators;k++){
  	if(i!=j && j!=k){
  	  SU_vector v1=(SU_vector::Generator(dim,i)+SU_vector::Generator(dim,j));
  	  SU_vector v2=SU_vector::Generator(dim,k);
  	  SU_vector v3=v2.UTransform(v1);
  	  SU_vector v4=(v2-v3.UTransform(-v1));
  	  auto out=v4.GetComponents();
  	  for(int di=0;di<dim*dim;di++){
	     if(fabs(out[di])>1e-10)
  	      std::cout <<i << "  " << j << "  " << k  <<"  Component: "<<di<<" --> " << out[di] << std::endl;
  	  }
  	}
      }
    }
  }
  
  return(0);
}
