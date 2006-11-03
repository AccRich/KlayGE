// D3D9ShaderObject.hpp
// KlayGE D3D9 shader对象类 头文件
// Ver 3.5.0
// 版权所有(C) 龚敏敏, 2006
// Homepage: http://klayge.sourceforge.net
//
// 3.5.0
// 初次建立 (2006.11.2)
//
// 修改记录
//////////////////////////////////////////////////////////////////////////////////

#ifndef _D3D9SHADEROBJECT_HPP
#define _D3D9SHADEROBJECT_HPP

#include <KlayGE/PreDeclare.hpp>
#include <KlayGE/ShaderObject.hpp>

#include <KlayGE/D3D9/D3D9Typedefs.hpp>

namespace KlayGE
{
#ifdef KLAYGE_PLATFORM_WINDOWS
#pragma pack(push, 1)
#endif
	struct D3D9ShaderParameterHandle
	{
		uint8_t shader_type;
		uint8_t register_set;

		uint16_t register_index;
		uint16_t register_count;

		uint8_t rows;
		uint8_t columns;
	};
#ifdef KLAYGE_PLATFORM_WINDOWS
#pragma pack(pop)
#endif

	class D3D9ShaderObject : public ShaderObject
	{
	public:
		void SetShader(ShaderType type, std::string const & profile, std::string const & name, std::string const & text);

		bool HasParameter(ShaderType type, std::string const & name) const;

		void SetParameter(std::string const & name, bool value);
		void SetParameter(std::string const & name, int value);
		void SetParameter(std::string const & name, float value);
		void SetParameter(std::string const & name, float4 const & value);
		void SetParameter(std::string const & name, float4x4 const & value);
		void SetParameter(std::string const & name, SamplerPtr const & value);
		void SetParameter(std::string const & name, std::vector<bool> const & value);
		void SetParameter(std::string const & name, std::vector<int> const & value);
		void SetParameter(std::string const & name, std::vector<float> const & value);
		void SetParameter(std::string const & name, std::vector<float4> const & value);
		void SetParameter(std::string const & name, std::vector<float4x4> const & value);

		ID3D9VertexShaderPtr VertexShader() const
		{
			return vertex_shader_;
		}
		ID3D9PixelShaderPtr PixelShader() const
		{
			return pixel_shader_;
		}

		uint32_t BoolStart(ShaderType type) const
		{
			return bool_start_[type];
		}
		uint32_t IntStart(ShaderType type) const
		{
			return int_start_[type];
		}
		uint32_t FloatStart(ShaderType type) const
		{
			return float_start_[type];
		}

		std::vector<BOOL> const & BoolRegisters(ShaderType type) const
		{
			return bool_registers_[type];
		}
		std::vector<int> const & IntRegisters(ShaderType type) const
		{
			return int_registers_[type];
		}
		std::vector<float> const & FloatRegisters(ShaderType type) const
		{
			return float_registers_[type];
		}

		std::vector<SamplerPtr> const & Samplers(ShaderType type) const
		{
			return samplers_[type];
		}

	private:
		typedef std::vector<std::pair<std::string, D3D9ShaderParameterHandle> > parameter_descs_t;
		boost::array<parameter_descs_t, ST_NumShaderTypes> param_descs_;

		ID3D9VertexShaderPtr vertex_shader_;
		ID3D9PixelShaderPtr pixel_shader_;

		boost::array<uint32_t, ST_NumShaderTypes> bool_start_;
		boost::array<uint32_t, ST_NumShaderTypes> int_start_;
		boost::array<uint32_t, ST_NumShaderTypes> float_start_;
		boost::array<std::vector<BOOL>, ST_NumShaderTypes> bool_registers_;
		boost::array<std::vector<int>, ST_NumShaderTypes> int_registers_;
		boost::array<std::vector<float>, ST_NumShaderTypes> float_registers_;
		boost::array<std::vector<SamplerPtr>, ST_NumShaderTypes> samplers_;
	};

	typedef boost::shared_ptr<D3D9ShaderObject> D3D9ShaderObjectPtr;
}

#endif			// _D3D9SHADEROBJECT_HPP
