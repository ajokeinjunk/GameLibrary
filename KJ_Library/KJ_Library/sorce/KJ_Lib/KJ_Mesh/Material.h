#pragma once

#include"Color.h"
#include <memory>

namespace Klibrary{

	class Material;
	typedef std::shared_ptr<Material> MaterialSharedPtr;
	typedef std::weak_ptr<Material> MaterialWeakPtr;

	class Material{
	public:
		ColorF m_Diffuse;  //RGBA
		ColorF m_Ambient;  //RGB
		ColorF m_Specular;
		ColorF m_Emissive;
		float  m_SpecularSharpness;

	public:
		Material() : m_Diffuse(BasicColor::White), m_Ambient(BasicColor::Gray), m_Specular(BasicColor::White),
			m_Emissive(BasicColor::White), m_SpecularSharpness(1.0f){}

		Material(const ColorF& diffuse, const ColorF& ambient, const ColorF& specular, const ColorF& emissive, float specularSharpness) :
			m_Diffuse(diffuse), m_Ambient(ambient), m_Specular(specular), m_Emissive(emissive), m_SpecularSharpness(specularSharpness){}


		void SetToDevice();
		/*
		void SetDiffuse(const ColorF& diffuse){ m_Diffuse = diffuse; }
		void SetAmbient(const ColorF& ambient){ m_Ambient = ambient; }
		void SetSpecular(const ColorF& specular){ m_Specular = specular; }
		void SetEmissive(const ColorF& emissive){ m_Emissive = emissive; }
		void SetSpecularSharpness(float specularSharpness){ m_SpecularSharpness = specularSharpness; }

		const ColorF& GetDiffuse()const{ return m_Diffuse; }
		const ColorF& GetAmbient()const{ return m_Ambient; }
		const ColorF& GetSpecular()const{ return m_Specular; }
		const ColorF& GetEmissive()const{ return m_Emissive; }
		float GetSpecularSharpness()const{ return m_SpecularSharpness; }*/
	};

}