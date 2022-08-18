 #include "Mandelbrot.h"

const int width_ = 1500;
const int height_ = 1500;
const int max_iterations_ = 80;



Mandelbrot::Mandelbrot()
{
	image_ = new uint32_t[width_ * height_];
}

Mandelbrot::~Mandelbrot()
{
}

void Mandelbrot::calculate(double real,double imag)
{

	//Range between -2, 1

	// c = (a + bi) * (a + bi)
	// a^2 + abi + abi + b^2 * i^2
	// i = sqrt(-1),  therefore, i^2 = -1
	// a^2 + abi + abi + b^2 * -1
	// a^2 + abi + abi - b^2
	// a^2 - b^2 + 2abi

	//angle_ += 0.005;
	//double temp_angle = angle_;
	float temp_real = real;
	float temp_imag = imag;
	concurrency::array_view<uint32_t, 2> a(width_,height_, image_);

	a.discard_data();

	concurrency::parallel_for_each(
		a.extent, 
		[=](concurrency::index<2> idx) restrict(amp)
	{
		int x = idx[0];
		int y = idx[1];

		CustomComplex c;
		c.real_ = temp_real;
		c.imag_ = temp_imag;
		CustomComplex z;
		z.real_ = -2.f + (x * 4.f / width_);
		z.imag_ = -2.f + (y * 4.f / height_);

		int n_ = 0;

		while (CustomComplex::c_abs(z) < 16.0 && n_ < max_iterations_)
		{
			z = CustomComplex::c_add(CustomComplex::c_mul(z, z), c);

			++n_;
		}

		if (n_ == max_iterations_)
		{
			//colors_[(int)n_%128]
			a[x][y] = 0x000000;
		}
		else
		{
			a[x][y] = n_ << 18;
		}
			
	});
	a.synchronize();
}

sf::Uint32 Mandelbrot::getPixel(int &x, int &y)
{
	return image_[(width_ * x) + y];
}

void Mandelbrot::write_tga(const char* filename)
{
	std::ofstream outfile(filename, std::ofstream::binary);

	uint8_t header[18] = {
		0, // no image ID
		0, // no colour map
		2, // uncompressed 24-bit image
		0, 0, 0, 0, 0, // empty colour map specification
		0, 0, // X origin
		0, 0, // Y origin
		width_ & 0xFF, (width_ >> 8) & 0xFF, // width
		height_ & 0xFF, (height_ >> 8) & 0xFF, // height
		24, // bits per pixel
		0, // image descriptor
	};
	outfile.write((const char*)header, 18);

	for (int y = 0; y < height_; ++y)
	{
		for (int x = 0; x < width_; ++x)
		{
			uint8_t pixel[3] = {
				image_[(width_ * x) + y] & 0xFF, // blue channel
				(image_[(width_ * x) + y] >> 8) & 0xFF, // green channel
				(image_[(width_ * x) + y] >> 16) & 0xFF, // red channel
			};
			outfile.write((const char*)pixel, 3);
		}
	}

	outfile.close();
	if (!outfile)
	{
		// An error has occurred at some point since we opened the file.
		std::cout << "Error writing to " << filename << std::endl;
		exit(1);
	}
}