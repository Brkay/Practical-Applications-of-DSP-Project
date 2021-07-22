function [converted_image,Elapsed_time] = gray_to_jet(varargin)
input_image = varargin{1};
color_map_type = string(varargin{2});
[row_number, column_number] = size(input_image);
switch color_map_type
    case "parula"
        C = uint8(255*parula); % Convert 0-1 numbers in colormap to 0-255 and conver uint8.
    case "turbo"
         C = uint8(255*turbo); 
    case "hsv"
         C = uint8(255*hsv); 
    case "hot"
         C = uint8(255*hot); 
    case "cool"
         C = uint8(255*cool); 
    case "spring"
         C = uint8(255*spring); 
    case "summer"
         C = uint8(255*summer); 
    case "autumn"
         C = uint8(255*autumn); 
    case "winter"
         C = uint8(255*winter); 
    case "gray"
         C = uint8(255*gray); 
    case "bone"
         C = uint8(255*bone); 
    case "pink"
         C = uint8(255*pink); 
    case "jet"
         C = uint8(255*jet); 
    case "lines"
         C = uint8(255*lines); 
    case "colorcube"
         C = uint8(255*colorcube); 
    case "prism"
         C = uint8(255*prism); 
    case "flag"
         C = uint8(255*flag); 
    case "white"
         C = uint8(255*white);   
end
converted_image = zeros(row_number, column_number, 3);
for idx = 1:row_number
    for jdx =1:column_number
        colormap_row  = double(input_image(idx, jdx) ) + 1;
        new_red_pixel = C(colormap_row, 1);
        new_green_pixel = C(colormap_row, 2);
        new_blue_pixel = C(colormap_row, 3);
        converted_image(idx, jdx, 1) = new_red_pixel;
        converted_image(idx, jdx, 2) = new_green_pixel;
        converted_image(idx, jdx, 3) = new_blue_pixel;
    end
end
converted_image = uint8(converted_image);
end