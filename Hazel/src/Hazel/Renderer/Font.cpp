#include "hzpch.h"
#include "Font.h"

#undef INFINITE
#include "msdf-atlas-gen.h"
#include "FontGeometry.h"
#include "GlyphGeometry.h"

namespace Hazel {

	struct MSDFData
	{
		std::vector<msdf_atlas::GlyphGeometry> Glyphs;
		msdf_atlas::FontGeometry FontGeometry;

	};
	
	template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
	static Ref<Texture2D> CreateAndCacheAtlas(const std::string& fontName, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
		const msdf_atlas::FontGeometry& fontGeometry, uint32_t width, uint32_t height)
	{
		msdf_atlas::GeneratorAttributes attributes;
		attributes.config.overlapSupport = true;
		attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
		generator.setAttributes(attributes);
		generator.setThreadCount(8);
		generator.generate(glyphs.data(), (int)glyphs.size());

		msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();

		TextureSpecification spec;
		spec.Width = bitmap.width;
		spec.Height = bitmap.height;
		spec.Format = ImageFormat::RGBA8;
		spec.GenerateMips = false;

		Ref<Texture2D> texture = Texture2D::Create(spec);
		texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * 3);
		return texture;
	}

	Font::Font(const std::filesystem::path& filepath)
		: m_Data(new MSDFData())
	{
		msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
		HZ_CORE_ASSERT(ft);
		
		std::string fileString = filepath.string();

		// TODO(Yan): msdfgen::loadFontData loads from memory buffer which we'll need 
		msdfgen::FontHandle* font = msdfgen::loadFont(ft, fileString.c_str());
		if (!font)
		{
			HZ_CORE_ERROR("Failed to load font: {}", fileString);
			return;
		}

		struct CharsetRange
		{
			uint32_t Begin, End;
		};

		// From imgui_draw.cpp
		static const CharsetRange charsetRanges[] =
		{
			{ 0x0020, 0x00FF }
		};

		msdf_atlas::Charset charset;
		for (CharsetRange range : charsetRanges)
		{
			for (uint32_t c = range.Begin; c <= range.End; c++)
				charset.add(c);
		}
		
		double fontScale = 1.0;
		m_Data->FontGeometry = msdf_atlas::FontGeometry(&m_Data->Glyphs);
		int glyphsLoaded = m_Data->FontGeometry.loadCharset(font, fontScale, charset);
		HZ_CORE_INFO("Loaded {} glyphs from font (out of {})", glyphsLoaded, charset.size());


		double emSize = 40.0;

		msdf_atlas::TightAtlasPacker atlasPacker;
		// atlasPacker.setDimensionsConstraint()
		atlasPacker.setPixelRange(2.0);
		atlasPacker.setMiterLimit(1.0);
		atlasPacker.setPadding(0);
		atlasPacker.setScale(emSize);
		int remaining = atlasPacker.pack(m_Data->Glyphs.data(), (int)m_Data->Glyphs.size());
		HZ_CORE_ASSERT(remaining == 0);

		int width, height;
		atlasPacker.getDimensions(width, height);
		emSize = atlasPacker.getScale();

		m_AtlasTexture = CreateAndCacheAtlas<uint8_t, float, 4, msdf_atlas::mtsdfGenerator>("Test", (float)emSize, m_Data->Glyphs, m_Data->FontGeometry, width, height);


#if 0
		msdfgen::Shape shape;
		if (msdfgen::loadGlyph(shape, font, 'C'))
		{
			shape.normalize();
			//                      max. angle
			msdfgen::edgeColoringSimple(shape, 3.0);
			//           image width, height
			msdfgen::Bitmap<float, 3> msdf(32, 32);
			//                     range, scale, translation
			msdfgen::generateMSDF(msdf, shape, 4.0, 1.0, msdfgen::Vector2(4.0, 4.0));
			msdfgen::savePng(msdf, "output.png");
		}
#endif

		msdfgen::destroyFont(font);
		msdfgen::deinitializeFreetype(ft);
	}

	Font::~Font()
	{
		delete m_Data;
	}

}
