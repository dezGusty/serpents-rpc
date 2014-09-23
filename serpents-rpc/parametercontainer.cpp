
#include "parametercontainer.h"

namespace serpents{
	
		ParameterContainer::ParameterContainer(const ParameterContainer& pc){
			for each (int var in pc.Impl_->intVec)
			{
				this->Impl_->intVec.push_back(var);
			}
			for each (double var in pc.Impl_->doubleVec)
			{
				this->Impl_->doubleVec.push_back(var);
			}
			for each (std::string var in pc.Impl_->stringVec)
			{
				this->Impl_->stringVec.push_back(var);
			}
			for each (std::string var in pc.Impl_->allVec)
			{
				this->Impl_->allVec.push_back(var);
			}
		}
		
		std::vector<int>& ParameterContainer::getInts(){
			return Impl_->intVec;
		}

		std::vector<double>& ParameterContainer::getDoubles(){
			return Impl_->doubleVec;
		}
		std::vector<std::string>& ParameterContainer::getStrings(){
			return Impl_->stringVec;
		}
		int ParameterContainer::getInt(unsigned int n){
			if (n < 0 || n > Impl_->allVec.size())
				throw(ParamContainerException("out of bounds exception"));
			try{
				return std::stoi(Impl_->allVec.at(n));
			}
			catch (std::exception& e){
				
				throw(ParamContainerException(std::string("invalid num")+e.what()));

			}
		}
		double ParameterContainer::getDouble(unsigned int n){
			try{
				if (n < 0 || n >Impl_->allVec.size())
					throw(ParamContainerException("out of bounds exception"));
				return std::stod(Impl_->allVec.at(n));
			}
			catch (std::exception& e){
				throw(ParamContainerException(std::string("invalid num")+e.what()));
			}
		}
		std::string ParameterContainer::getString(unsigned int n){
			try{
				if (n < 0 || n > Impl_->allVec.size())
					throw(ParamContainerException("out of bounds exception"));
				return Impl_->allVec.at(n);
			}
			catch (std::exception& e){
				throw(ParamContainerException(std::string("no string found",e.what())));
			}
		}

		unsigned int ParameterContainer::size(){
			return Impl_->allVec.size();
		}
		std::string ParameterContainer::getType(unsigned int n){
			if (n > Impl_->typeVec.size()){
				throw(ParamContainerException("no string found"));
			}
			int t = Impl_->typeVec.at(n);
			switch (t){
				case type::Int:  return "Int"; break;
				case type::Double:return "Double"; break;
				case type::Bool: return "Bool"; break;
				case type::Float: return "Float"; break;
				case type::String: return "String";  break;
			}
			throw(ParamContainerException("type not supported"));
		}
		void ParameterContainer::push(std::string s){
			Impl_->allVec.push_back(s);
		}
		std::string ParameterContainer::pop(){
			if (Impl_->allVec.size() >= 1){
				std::string s = Impl_->allVec.at(Impl_->allVec.size() - 1);
				Impl_->allVec.pop_back();
				return s;
			}
			else{
				return "";
			}
		}
		std::vector<std::string>& ParameterContainer::getAll(){
			return Impl_->allVec;
		}
		ParameterContainer::~ParameterContainer(){
			delete Impl_;
		}
}
