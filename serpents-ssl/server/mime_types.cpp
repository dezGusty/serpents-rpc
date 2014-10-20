//   This file is part of the serpents-rpc library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  The serpents-rpc team (See AUTHORS file)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.


#include "mime_types.hpp"
namespace serpents{
	namespace http {
		namespace server2 {
			namespace mime_types {

				struct mapping
				{
					const char* extension;
					const char* mime_type;
				} mappings[] =
				{
					{ "gif", "image/gif" },
					{ "htm", "text/html" },
					{ "html", "text/html" },
					{ "jpg", "image/jpeg" },
					{ "png", "image/png" },
					{ 0, 0 } // Marks end of list.
				};

				std::string extension_to_type(const std::string& extension)
				{
					for (mapping* m = mappings; m->extension; ++m)
					{
						if (m->extension == extension)
						{
							return m->mime_type;
						}
					}

					return "text/plain";
				}

			} // namespace mime_types
		} // namespace server2
	} // namespace http
} //namespace serpents